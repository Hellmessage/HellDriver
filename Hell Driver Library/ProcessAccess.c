#include "SSDT.h"
#include "ProcessAccess.h"

#define TYPE_CHECK(type, code)                               ((type->Info.AccessType & code) == code)
#define ACCESS_ELIMINATE(access, eliminate)                  access &= ~eliminate

static const ULONG g_Tag = 'pac';

typedef struct _HELL_PROCESS_ACCESS_MANAGE {
    LIST_ENTRY                      ListEntry;
    HELL_PROCESS_ACCESS_OPT         Info;
    ACCESS_MASK                     BackupAccess;
}HELL_PROCESS_ACCESS_MANAGE, * PHELL_PROCESS_ACCESS_MANAGE;

PHELL_PROCESS_ACCESS_MANAGE GetManageByPid(UINT32 pid);

OB_PREOP_CALLBACK_STATUS ObProcessAccessFirstHookCall(PVOID content, POB_PRE_OPERATION_INFORMATION oper);
OB_PREOP_CALLBACK_STATUS ObProcessAccessLastHookCall(PVOID content, POB_PRE_OPERATION_INFORMATION oper);

static OB_OPERATION_REGISTRATION ObProcessAccessFirstOpt[] = {
    { NULL, OB_OPERATION_HANDLE_CREATE | OB_OPERATION_HANDLE_DUPLICATE, ObProcessAccessFirstHookCall, NULL},
    { NULL, OB_OPERATION_HANDLE_CREATE | OB_OPERATION_HANDLE_DUPLICATE, ObProcessAccessFirstHookCall, NULL},
};
static OB_CALLBACK_REGISTRATION ObProcessAccessFirstCallBack = { OB_FLT_REGISTRATION_VERSION, 2, {0}, NULL, ObProcessAccessFirstOpt };

static OB_OPERATION_REGISTRATION ObProcessAccessLastOpt[] = {
    { NULL, OB_OPERATION_HANDLE_CREATE | OB_OPERATION_HANDLE_DUPLICATE, ObProcessAccessLastHookCall, NULL},
    { NULL, OB_OPERATION_HANDLE_CREATE | OB_OPERATION_HANDLE_DUPLICATE, ObProcessAccessLastHookCall, NULL},
};
static OB_CALLBACK_REGISTRATION ObProcessAccessLastCallBack = { OB_FLT_REGISTRATION_VERSION, 2, {0}, NULL, ObProcessAccessLastOpt };

static HANDLE g_ObProcessAccessFirstHandle = NULL;
static HANDLE g_ObProcessAccessLastHandle = NULL;
static BOOLEAN g_Installed = FALSE;

static LIST_ENTRY g_ListHead;
static KSPIN_LOCK g_Lock;

NTSTATUS ProcessAccessHookInstall() {
    if (!g_Installed) {
        KeInitializeSpinLock(&g_Lock);
        InitializeListHead(&g_ListHead);

        ObProcessAccessFirstOpt[0].ObjectType = PsProcessType;
        ObProcessAccessFirstOpt[1].ObjectType = PsThreadType;
        RtlInitUnicodeString(&ObProcessAccessFirstCallBack.Altitude, L"999999");
        ObProcessAccessLastOpt[0].ObjectType = PsProcessType;
        ObProcessAccessLastOpt[1].ObjectType = PsThreadType;
        RtlInitUnicodeString(&ObProcessAccessLastCallBack.Altitude, L"1000");
        
        NTSTATUS status = ObRegisterCallbacks(&ObProcessAccessFirstCallBack, &g_ObProcessAccessFirstHandle);
        if (status == STATUS_SUCCESS) {
            HLog("ע����Ȩ�ص��ɹ�: %p", g_ObProcessAccessFirstHandle);
            status = ObRegisterCallbacks(&ObProcessAccessLastCallBack, &g_ObProcessAccessLastHandle);
            if (status != STATUS_SUCCESS) {
                HLog("ע�ήȨ�ص�ʧ��: %d", status);
                ObUnRegisterCallbacks(g_ObProcessAccessFirstHandle);
            }
        }

        g_Installed = (status == STATUS_SUCCESS);
        HLog("������Ȩ/��Ȩ HOOK %d", g_Installed);
        return status;
    }
    return STATUS_SUCCESS;
}

NTSTATUS ProcessAccessHookUninstall() {
    if (g_Installed) {
        ObUnRegisterCallbacks(g_ObProcessAccessFirstHandle);
        ObUnRegisterCallbacks(g_ObProcessAccessLastHandle);
        HLog("������Ȩ/��Ȩ HOOK ���˳�");
        g_Installed = FALSE;
    }
    return STATUS_SUCCESS;
}

OB_PREOP_CALLBACK_STATUS ObProcessAccessFirstHookCall(PVOID content, POB_PRE_OPERATION_INFORMATION oper) {
    HELL_PARAMS(content);
    HELL_PARAMS(oper);

    if (*PsProcessType != oper->ObjectType) {
        return OB_PREOP_SUCCESS;
    }
    if (oper->Operation == OB_OPERATION_HANDLE_DUPLICATE) {
        return OB_PREOP_SUCCESS;
    }

    HANDLE callingProcessId = PsGetCurrentProcessId();
    PEPROCESS targetProcess = (PEPROCESS)oper->Object;
    HANDLE targetProcessId = PsGetProcessId(targetProcess);

    UINT32 cpid = (UINT32)((UINT64)callingProcessId);
    UINT32 tpid = (UINT32)((UINT64)targetProcessId);
    ACCESS_MASK oAccess = oper->Parameters->CreateHandleInformation.OriginalDesiredAccess;

    HELL_IN_LOCK(&g_Lock);

    PHELL_PROCESS_ACCESS_MANAGE manage = GetManageByPid(cpid);
    if (manage == NULL) {
        manage = GetManageByPid(tpid);
    }

    if (manage != NULL) {
        manage->BackupAccess = oAccess;
    }

    HELL_UN_LOCK(&g_Lock);
    return OB_PREOP_SUCCESS;
}

OB_PREOP_CALLBACK_STATUS ObProcessAccessLastHookCall(PVOID content, POB_PRE_OPERATION_INFORMATION oper) {
    HELL_PARAMS(content);
    HELL_PARAMS(oper);

    if (*PsProcessType != oper->ObjectType) {
        return OB_PREOP_SUCCESS;
    }
    if (oper->Operation == OB_OPERATION_HANDLE_DUPLICATE) {
        return OB_PREOP_SUCCESS;
    }

    HANDLE callingProcessId = PsGetCurrentProcessId();
    PUCHAR callingProcessName = PsGetProcessImageFileName(PsGetCurrentProcess());

    PEPROCESS targetProcess = (PEPROCESS)oper->Object;
    HANDLE targetProcessId = PsGetProcessId(targetProcess);
    PUCHAR targetProcessName = PsGetProcessImageFileName(targetProcess);

    UINT32 cpid = (UINT32)((UINT64)callingProcessId);
    UINT32 tpid = (UINT32)((UINT64)targetProcessId);

    ACCESS_MASK oAccess = oper->Parameters->CreateHandleInformation.OriginalDesiredAccess;
    ACCESS_MASK nAccess = oper->Parameters->CreateHandleInformation.DesiredAccess;

    HELL_IN_LOCK(&g_Lock);

    PHELL_PROCESS_ACCESS_MANAGE manage = GetManageByPid(tpid);
    if (manage == NULL) {
        manage = GetManageByPid(cpid);
    }

    if (manage != NULL) {
        ACCESS_MASK access = nAccess;
        if (tpid == manage->Info.ProcessId) {
            //������
            if (TYPE_CHECK(manage, HPAT_PROTECT)) {
                ACCESS_ELIMINATE(access, manage->Info.Access);
            }
        } else {
            //������
            if (TYPE_CHECK(manage, HPAT_ENHANCE)) {//���Ȩ��
                access |= manage->Info.Access;
            } if (TYPE_CHECK(manage, HPAT_MAINTAIN)) {//ά��Ȩ��
                access = manage->BackupAccess;
            } else if (TYPE_CHECK(manage, HPAT_REDUCE)) {//����Ȩ��
                ACCESS_ELIMINATE(access, manage->Info.Access);
            }
        }
        if (nAccess != access) {
            HLog("�޸�Ȩ�� ����ID:%d ����:%d Ȩ��:%d  ���ý���:%s Ŀ�����:%s ����Ȩ��:%d ��ǰȨ��:%d ����Ȩ��:%d",
                manage->Info.ProcessId,
                manage->Info.AccessType,
                manage->Info.Access,
                callingProcessName, targetProcessName, manage->BackupAccess, oAccess, access);
            oper->Parameters->CreateHandleInformation.OriginalDesiredAccess = access;
            oper->Parameters->CreateHandleInformation.DesiredAccess = access;
        }
    }
    HELL_UN_LOCK(&g_Lock);
    return OB_PREOP_SUCCESS;
}

PHELL_PROCESS_ACCESS_MANAGE GetManageByPid(UINT32 pid) {
    PHELL_PROCESS_ACCESS_MANAGE result = NULL;
    if (g_Installed) {
        PLIST_ENTRY entry;
        for (entry = g_ListHead.Flink; entry != &g_ListHead; entry = entry->Flink) {
            PHELL_PROCESS_ACCESS_MANAGE data = CONTAINING_RECORD(entry, HELL_PROCESS_ACCESS_MANAGE, ListEntry);
            if (data->Info.ProcessId == pid) {
                result = data;
                break;
            }
        }
    }
    return result;
}

void ProcessAccessClear() {
    if (g_Installed) {
        HELL_IN_LOCK(&g_Lock);
        while (!IsListEmpty(&g_ListHead)) {
            PLIST_ENTRY entry = RemoveHeadList(&g_ListHead);
            PHELL_PROCESS_ACCESS_MANAGE data = CONTAINING_RECORD(entry, HELL_PROCESS_ACCESS_MANAGE, ListEntry);
            HLog("�Ƴ����� ����ID:%d ����:%x Ȩ��:%d", data->Info.ProcessId, data->Info.AccessType, data->Info.Access);
            ExFreePoolWithTag(data, g_Tag);
        }
        HELL_UN_LOCK(&g_Lock);
    }
}

BOOLEAN ProcessAccessSetHook(PHELL_PROCESS_ACCESS_OPT opt) {
    if (g_Installed) {
        HELL_IN_LOCK(&g_Lock);
        PLIST_ENTRY entry;
        PHELL_PROCESS_ACCESS_MANAGE manage = NULL;
        for (entry = g_ListHead.Flink; entry != &g_ListHead; entry = entry->Flink) {
            PHELL_PROCESS_ACCESS_MANAGE data = CONTAINING_RECORD(entry, HELL_PROCESS_ACCESS_MANAGE, ListEntry);
            if (data->Info.ProcessId == opt->ProcessId) {
                manage = data;
                break;
            }
        }
        if (manage == NULL) {
            manage = (PHELL_PROCESS_ACCESS_MANAGE)ExAllocatePool2(POOL_FLAG_NON_PAGED, sizeof(HELL_PROCESS_ACCESS_MANAGE), g_Tag);
            if (manage == NULL) {
                HELL_UN_LOCK(&g_Lock);
                return FALSE;
            }
            RtlZeroMemory(manage, sizeof(HELL_PROCESS_ACCESS_MANAGE));
            manage->BackupAccess = 0;
            InsertHeadList(&g_ListHead, &manage->ListEntry);
        }
        manage->Info.ProcessId = opt->ProcessId;
        manage->Info.Access = opt->Access;
        manage->Info.AccessType = opt->AccessType;
        HLog("--------------���ý���<%d>�����ɹ�", manage->Info.ProcessId);
        HELL_UN_LOCK(&g_Lock);
        EnumRegisterHookCallBacks();
        return TRUE;
    }
    return FALSE;
}

BOOLEAN ProcessAccessDelHook(PHELL_PROCESS_ACCESS_OPT opt) {
    if (g_Installed) {
        HELL_IN_LOCK(&g_Lock);
        PLIST_ENTRY entry;
        for (entry = g_ListHead.Flink; entry != &g_ListHead; entry = entry->Flink) {
            PHELL_PROCESS_ACCESS_MANAGE data = CONTAINING_RECORD(entry, HELL_PROCESS_ACCESS_MANAGE, ListEntry);
            if (data->Info.ProcessId == opt->ProcessId) {
                RemoveEntryList(entry);
                ExFreePoolWithTag(data, g_Tag);
                break;
            }
        }
        HELL_UN_LOCK(&g_Lock);
        return TRUE;
    }
    return FALSE;
}