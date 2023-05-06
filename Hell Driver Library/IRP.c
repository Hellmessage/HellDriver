#include "Hell.h"
#include "Memory.h"
#include "SSDTHook.h"

void InSSDTProtect(PIRP pirp, PIO_STACK_LOCATION stack);
void UnSSDTProtect(PIRP pirp, PIO_STACK_LOCATION stack);
UINT32 KEProcessMemoryRead(PIRP pirp, PIO_STACK_LOCATION stack);
UINT32 KEProcessMemoryMDLRead(PIRP pirp, PIO_STACK_LOCATION stack);
UINT32 KEProcessMemoryMDLWrite(PIRP pirp, PIO_STACK_LOCATION stack);


NTSTATUS IRPHandle(PDEVICE_OBJECT pDevice, PIRP pirp) {
    HELL_PARAMS(pDevice);
    HELL_PARAMS(pirp);

    HLog("���� IRP ��ǲ");
    PIO_STACK_LOCATION stack;
    stack = IoGetCurrentIrpStackLocation(pirp);
    switch (stack->MajorFunction) {
        case IRP_MJ_CREATE:
            HLog("��ǲ IRP_MJ_CREATE");
            break;
        case IRP_MJ_CLOSE:
            HLog("��ǲ IRP_MJ_CLOSE");
            break;
        default:
            HLog("��ǲ IRP = %X", stack->MajorFunction);
            break;
    }
    pirp->IoStatus.Status = STATUS_SUCCESS;
    pirp->IoStatus.Information = 4;
    IoCompleteRequest(pirp, IO_NO_INCREMENT);
    HLog("�뿪IRP");
    return STATUS_SUCCESS;
}

NTSTATUS IRPIoControl(PDEVICE_OBJECT pDevice, PIRP pirp) {
    HLog("���� IRPIoControl");
    HELL_PARAMS(pDevice);
    HELL_PARAMS(pirp);
    
    PIO_STACK_LOCATION stack;
    ULONG code;
    stack = IoGetCurrentIrpStackLocation(pirp);
    code = stack->Parameters.DeviceIoControl.IoControlCode;
    HLog("IRPIoControl Code = %X", code);

    pirp->IoStatus.Status = STATUS_SUCCESS;
    pirp->IoStatus.Information = 4;

    switch (code) {
        case CODE_LOAD_SSDTHOOK:
            LoadSSDTHook();
            break;
        case CODE_UNLOAD_SSDTHOOK:
            UnloadSSDTHook();
            break;
        case CODE_IN_SSDT_PROTECT:
            InSSDTProtect(pirp, stack);
            break;
        case CODE_UN_SSDT_PROTECT:
            UnSSDTProtect(pirp, stack);
            break;
        case CODE_KE_READ_MEMORY:
            pirp->IoStatus.Information = KEProcessMemoryRead(pirp, stack);
            break;
        case CODE_KE_READ_MEMORY_MDL:
            pirp->IoStatus.Information = KEProcessMemoryMDLRead(pirp, stack);
            break;
        case CODE_KE_WRITE_MEMORY:

            break;
        default:
            break;
    }
    IoCompleteRequest(pirp, IO_NO_INCREMENT);
    HLog("�뿪 IRPIoControl");
    return STATUS_SUCCESS;
}

void InSSDTProtect(PIRP pirp, PIO_STACK_LOCATION stack) {
    HELL_PARAMS(pirp);
    HELL_PARAMS(stack);
    
    ULONG length = sizeof(ProtectProcessItem);
    PProtectProcessItem temp = (PProtectProcessItem)ExAllocatePool2(POOL_FLAG_NON_PAGED, length, 'temp');
    if (temp != NULL) {
        RtlZeroMemory(temp, length);
        RtlCopyMemory(temp, pirp->AssociatedIrp.SystemBuffer, length);
        AddSSDTProtect(temp->ProcessId, temp->ExcludeAccess);
        ExFreePoolWithTag(temp, 'temp');
    }
}

void UnSSDTProtect(PIRP pirp, PIO_STACK_LOCATION stack) {
    HELL_PARAMS(pirp);
    HELL_PARAMS(stack);

    ULONG length = sizeof(ProtectProcessItem);
    PProtectProcessItem temp = (PProtectProcessItem)ExAllocatePool2(POOL_FLAG_NON_PAGED, length, 'temp');
    if (temp != NULL) {
        RtlZeroMemory(temp, length);
        RtlCopyMemory(temp, pirp->AssociatedIrp.SystemBuffer, length);
        RemoveSSDTProtect(temp->ProcessId);
        ExFreePoolWithTag(temp, 'temp');
    }
}

UINT32 KEProcessMemoryRead(PIRP pirp, PIO_STACK_LOCATION stack) {
    HELL_PARAMS(pirp);
    HELL_PARAMS(stack);
    UINT32 readLen = 0;
    ULONG length = sizeof(ProcessMemoryOpt);
    PProcessMemoryOpt opt = (PProcessMemoryOpt)ExAllocatePool2(POOL_FLAG_NON_PAGED, length, 'opt');
    if (opt != NULL && MmIsAddressValid(opt)) {
        RtlZeroMemory(opt, length);
        RtlCopyMemory(opt, pirp->AssociatedIrp.SystemBuffer, length);
        PVOID buffer = ExAllocatePool2(POOL_FLAG_NON_PAGED, opt->Length, 'buf');
        if (buffer == NULL) {
            ExFreePoolWithTag(opt, 'opt');
            pirp->IoStatus.Status = STATUS_UNSUCCESSFUL;
        } else {
            NTSTATUS status = KReadProcessMemoryByPid((UINT32)opt->ProcessId, (PVOID)opt->Address, opt->Length, buffer);
            pirp->IoStatus.Status = status;
            if (status == STATUS_SUCCESS) {
                RtlCopyMemory(pirp->AssociatedIrp.SystemBuffer, buffer, opt->Length);
                readLen = opt->Length;
                UNICODE_STRING str;
                RtlInitUnicodeString(&str, (PCWSTR)buffer);
                HLog("��������: %wZ", str);
                ExFreePoolWithTag(buffer, 'buf');
                ExFreePoolWithTag(opt, 'opt');
            }
        }
    } else {
        pirp->IoStatus.Status = STATUS_UNSUCCESSFUL;
    }
    return readLen;
}

UINT32 KEProcessMemoryMDLRead(PIRP pirp, PIO_STACK_LOCATION stack) {
    HELL_PARAMS(pirp);
    HELL_PARAMS(stack);
    UINT32 readLen = 0;
    ULONG length = sizeof(ProcessMemoryOpt);
    PProcessMemoryOpt opt = (PProcessMemoryOpt)ExAllocatePool2(POOL_FLAG_NON_PAGED, length, 'opt');
    if (opt != NULL && MmIsAddressValid(opt)) {
        RtlZeroMemory(opt, length);
        RtlCopyMemory(opt, pirp->AssociatedIrp.SystemBuffer, length);
        NTSTATUS status = KReadProcessMemoryByPid((UINT32)opt->ProcessId, (PVOID)opt->Address, opt->Length, opt->UserBuffer);
        pirp->IoStatus.Status = status;
        if (status == STATUS_SUCCESS) {
            readLen = opt->Length;
            UNICODE_STRING str;
            RtlInitUnicodeString(&str, (PCWSTR)opt->UserBuffer);
            HLog("��������: %wZ", str);
            ExFreePoolWithTag(opt, 'opt');
        }
    } else {
        pirp->IoStatus.Status = STATUS_UNSUCCESSFUL;
    }
    return readLen;
}

UINT32 KEProcessMemoryMDLWrite(PIRP pirp, PIO_STACK_LOCATION stack) {
    HELL_PARAMS(pirp);
    HELL_PARAMS(stack);
    UINT32 readLen = 0;
    ULONG length = sizeof(ProcessMemoryOpt);
    PProcessMemoryOpt opt = (PProcessMemoryOpt)ExAllocatePool2(POOL_FLAG_NON_PAGED, length, 'opt');
    if (opt != NULL && MmIsAddressValid(opt)) {
        RtlZeroMemory(opt, length);
        RtlCopyMemory(opt, pirp->AssociatedIrp.SystemBuffer, length);
        NTSTATUS status = KWriteProcessMemoryByPid((UINT32)opt->ProcessId, (PVOID)opt->Address, opt->Length, opt->UserBuffer);
        pirp->IoStatus.Status = status;
        if (status == STATUS_SUCCESS) {
            readLen = opt->Length;
            HLog("д���ڴ�");
            ExFreePoolWithTag(opt, 'opt');
        }
    } else {
        pirp->IoStatus.Status = STATUS_UNSUCCESSFUL;
    }
    return readLen;
}
