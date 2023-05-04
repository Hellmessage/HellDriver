#include "Hell.h"

NTSTATUS IRPHandle(PDEVICE_OBJECT pDevice, PIRP pirp) {
    HELL_PARAMS(pDevice);
    HELL_PARAMS(pirp);

    HLog("进入 IRP 派遣");
    PIO_STACK_LOCATION stack;
    stack = IoGetCurrentIrpStackLocation(pirp);
    switch (stack->MajorFunction) {
        case IRP_MJ_CREATE:
            HLog("派遣 IRP_MJ_CREATE");
            break;
        case IRP_MJ_CLOSE:
            HLog("派遣 IRP_MJ_CLOSE");
            break;
        default:
            HLog("派遣 IRP<%X>", stack->MajorFunction);
            break;
    }
    pirp->IoStatus.Status = STATUS_SUCCESS;
    pirp->IoStatus.Information = 4;
    IoCompleteRequest(pirp, IO_NO_INCREMENT);
    HLog("离开IRP");
    return STATUS_SUCCESS;
}

NTSTATUS IRPIoControl(PDEVICE_OBJECT pDevice, PIRP pirp) {
    HLog("进入 IRPIoControl");
    HELL_PARAMS(pDevice);
    HELL_PARAMS(pirp);
    
    PIO_STACK_LOCATION stack;
    ULONG code;
    ULONG length;
    stack = IoGetCurrentIrpStackLocation(pirp);
    code = stack->Parameters.DeviceIoControl.IoControlCode;
    length = stack->Parameters.DeviceIoControl.InputBufferLength;

    HLog("IRPIoControl Code = %X 长度 = %d", code, length);

    switch (code) {
        case HCODE(0x803):
            
            break;
        default:
            break;
    }



    pirp->IoStatus.Status = STATUS_SUCCESS;
    pirp->IoStatus.Information = 4;
    IoCompleteRequest(pirp, IO_NO_INCREMENT);
    HLog("离开 IRPIoControl");
    return STATUS_SUCCESS;
}
