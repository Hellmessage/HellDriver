#include "Hell.h"
#include "SSDTHook.h"

void ReadHandle(PIRP pirp, PIO_STACK_LOCATION stack);
void WriteHandle(PIRP pirp, PIO_STACK_LOCATION stack);
void InSSDTProtect(PIRP pirp, PIO_STACK_LOCATION stack);
void UnSSDTProtect(PIRP pirp, PIO_STACK_LOCATION stack);

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
        case CODE_WRITE:
            WriteHandle(pirp, stack);
            break;
        case CODE_READ:
            ReadHandle(pirp, stack);
            break;
        case CODE_READ_WRITE:
            break;
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
        default:
            break;
    }

    IoCompleteRequest(pirp, IO_NO_INCREMENT);
    HLog("�뿪 IRPIoControl");
    return STATUS_SUCCESS;
}

void ReadHandle(PIRP pirp, PIO_STACK_LOCATION stack) {
    HELL_PARAMS(pirp);
    HELL_PARAMS(stack);

}

void WriteHandle(PIRP pirp, PIO_STACK_LOCATION stack) {
    HELL_PARAMS(pirp);
    HELL_PARAMS(stack);
}

void InSSDTProtect(PIRP pirp, PIO_STACK_LOCATION stack) {
    HELL_PARAMS(pirp);
    HELL_PARAMS(stack);
    
    ULONG length = sizeof(ProtectProcessItem);
    PProtectProcessItem temp = (PProtectProcessItem)ExAllocatePool2(POOL_FLAG_PAGED, length, 'temp');
    if (temp != NULL) {
        memset(temp, 0x0, length);
        memcpy(temp, pirp->AssociatedIrp.SystemBuffer, length);
        AddSSDTProtect(temp->ProcessId, temp->ExcludeAccess);
        ExFreePoolWithTag(temp, 'temp');
    }
}

void UnSSDTProtect(PIRP pirp, PIO_STACK_LOCATION stack) {
    HELL_PARAMS(pirp);
    HELL_PARAMS(stack);

    ULONG length = sizeof(ProtectProcessItem);
    PProtectProcessItem temp = (PProtectProcessItem)ExAllocatePool2(POOL_FLAG_PAGED, length, 'temp');
    if (temp != NULL) {
        memset(temp, 0x0, length);
        memcpy(temp, pirp->AssociatedIrp.SystemBuffer, length);
        RemoveSSDTProtect(temp->ProcessId);
        ExFreePoolWithTag(temp, 'temp');
    }
}
