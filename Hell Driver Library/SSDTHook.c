#include "SSDTHook.h"
#include "HUtil.h"

void InitSSDTProtect();
PProtectProcessItem GetProtectByPid(UINT32 pid);
OB_PREOP_CALLBACK_STATUS SSDTHook(PVOID content, POB_PRE_OPERATION_INFORMATION oper);

const ULONG g_Tag = 'ssdt';
HANDLE g_SSDTHandleCallBack = NULL;
INT32 g_ProtectSize = 0;
BOOLEAN g_InitProtect = FALSE;
LIST_ENTRY g_ProtectList;
KSPIN_LOCK g_Lock;

PProtectProcessItem GetProtectByPid(UINT32 pid) {
    if (g_InitProtect) {
        HELL_IN_LOCK(&g_Lock);
        if (g_ProtectSize > 0) {
            PLIST_ENTRY temp = g_ProtectList.Flink;
            do {
                PProtectProcessItem pdata = CONTAINING_RECORD(temp, ProtectProcessItem, ListEntry);
                if (pdata->ProcessId == pid) {
                    HELL_UN_LOCK(&g_Lock);
                    return pdata;
                }
                temp = pdata->ListEntry.Flink;
            } while (temp != g_ProtectList.Blink);
        }
        HELL_UN_LOCK(&g_Lock);
    }
    return NULL;
}

void FreeSSDTProtect() {
    if (g_InitProtect) {
        HELL_IN_LOCK(&g_Lock);
        if (g_ProtectSize > 0) {
            while (!IsListEmpty(&g_ProtectList)) {
                PLIST_ENTRY pEntry = RemoveHeadList(&g_ProtectList);
                PProtectProcessItem pdata = CONTAINING_RECORD(pEntry, ProtectProcessItem, ListEntry);
                HLog("移除保护 pid:%d access:%u", pdata->ProcessId, pdata->ExcludeAccess);
                ExFreePoolWithTag(pdata, g_Tag);
            }
        }
        HELL_UN_LOCK(&g_Lock);
    }
}

void AddSSDTProtect(UINT32 pid, ACCESS_MASK access) {
    if (g_InitProtect) {
        HELL_IN_LOCK(&g_Lock);
        PProtectProcessItem old = NULL;
        if (g_ProtectSize > 0) {
            PLIST_ENTRY temp = g_ProtectList.Flink;
            do {
                PProtectProcessItem pdata = CONTAINING_RECORD(temp, ProtectProcessItem, ListEntry);
                if (pdata->ProcessId == pid) {
                    old = pdata;
                    break;
                }
                temp = pdata->ListEntry.Flink;
            } while (temp != g_ProtectList.Blink);
        }

        if (old == NULL) {
            PProtectProcessItem protect = (PProtectProcessItem)ExAllocatePool2(POOL_FLAG_PAGED, sizeof(ProtectProcessItem), g_Tag);
            if (protect != NULL) {
                RtlZeroMemory(protect, sizeof(ProtectProcessItem));
                protect->ProcessId = pid;
                protect->ExcludeAccess = access;
                InsertHeadList(&g_ProtectList, &protect->ListEntry);
                HLog("载入保护<%d> pid:%d access:%u", g_ProtectSize, protect->ProcessId, protect->ExcludeAccess);
                g_ProtectSize++;
            }
        } else {
            old->ExcludeAccess = access;
            HLog("修改保护 pid:%d access:%u", old->ProcessId, old->ExcludeAccess);
        }
        HELL_UN_LOCK(&g_Lock);
    }
}
void RemoveSSDTProtect(UINT32 pid) {
    if (g_InitProtect) {
        HELL_IN_LOCK(&g_Lock);
        if (g_ProtectSize > 0) {
            PLIST_ENTRY temp = g_ProtectList.Flink;
            do {
                PProtectProcessItem pdata = CONTAINING_RECORD(temp, ProtectProcessItem, ListEntry);
                if (pdata->ProcessId == pid) {
                    HLog("移除保护 pid:%d access:%u", pdata->ProcessId, pdata->ExcludeAccess);
                    RemoveEntryList(&pdata->ListEntry);
                    ExFreePoolWithTag(pdata, g_Tag);
                    g_ProtectSize--;
                    break;
                }
                temp = pdata->ListEntry.Flink;
            } while (temp != g_ProtectList.Blink);
        }
        HELL_UN_LOCK(&g_Lock);
    }
}

void InitSSDTProtect() {
    if (!g_InitProtect) {
        g_InitProtect = TRUE;
        KeInitializeSpinLock(&g_Lock);
        if (g_ProtectSize <= 0) {
            InitializeListHead(&g_ProtectList);
        }
    }
}



NTSTATUS LoadSSDTHook() {
    if (g_SSDTHandleCallBack == NULL) {
        InitSSDTProtect();
        OB_CALLBACK_REGISTRATION call = { 0 };
        OB_OPERATION_REGISTRATION oper = { 0 };
        RtlInitUnicodeString(&call.Altitude, L"321000");
        call.RegistrationContext = NULL;
        call.Version = OB_FLT_REGISTRATION_VERSION;
        call.OperationRegistrationCount = 1;
        call.OperationRegistration = &oper;
        oper.ObjectType = PsProcessType;
        oper.Operations = OB_OPERATION_HANDLE_CREATE;
        oper.PostOperation = NULL;
        oper.PreOperation = SSDTHook;
        NTSTATUS status = ObRegisterCallbacks(&call, &g_SSDTHandleCallBack);
        if (status == STATUS_SUCCESS) {
            HLog("SSDT Hook 成功");
        } else {
            HLog("SSDT Hook 失败 ErrorCode = %x", status);
        }
        return status;
    } else {
        HLog("SSDT Hook 已加载");
        return STATUS_SUCCESS;
    }
}

void UnloadSSDTHook() {
    if (g_SSDTHandleCallBack != NULL) {
        ObUnRegisterCallbacks(g_SSDTHandleCallBack);
        g_SSDTHandleCallBack = NULL;
        HLog("SSDT Hook 已卸载");
    }
}

OB_PREOP_CALLBACK_STATUS SSDTHook(PVOID content, POB_PRE_OPERATION_INFORMATION oper) {
    HELL_PARAMS(content);
    HELL_PARAMS(oper);
    if (*PsProcessType != oper->ObjectType) {
        return OB_PREOP_SUCCESS;
    }

    HANDLE callingProcessId = PsGetCurrentProcessId();
    PUCHAR callingProcessName = PsGetProcessImageFileName(PsGetCurrentProcess());
    PEPROCESS targetProcess = (PEPROCESS)oper->Object;
    HANDLE targetProcessId = PsGetProcessId(targetProcess);
    PUCHAR targetProcessName = PsGetProcessImageFileName(targetProcess);

    UINT32 cpid = (UINT32)((UINT64)callingProcessId);
    UINT32 tpid = (UINT32)((UINT64)targetProcessId);
    PProtectProcessItem item = GetProtectByPid(tpid);
    if (item == NULL) {
        return OB_PREOP_SUCCESS;
    }

    if (oper->KernelHandle == 0) {
        ACCESS_MASK oAccess = oper->Parameters->CreateHandleInformation.OriginalDesiredAccess;
        HELL_PARAMS(oAccess);
        ACCESS_MASK nAccess = oAccess;
        HELL_PARAMS(nAccess);
        nAccess &= ~item->ExcludeAccess;
        oper->Parameters->CreateHandleInformation.DesiredAccess = nAccess;
        HLog("SSDT HOOK -> process: %s(%d) - %s(%d)  老权限: 0x%x 新权限: 0x%x", targetProcessName, tpid, callingProcessName, cpid, oAccess, nAccess);
    }

    return OB_PREOP_SUCCESS;
}
