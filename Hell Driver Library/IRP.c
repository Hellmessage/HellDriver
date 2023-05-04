#include "Hell.h"

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
            HLog("��ǲ IRP<%X>", stack->MajorFunction);
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
    ULONG length;
    stack = IoGetCurrentIrpStackLocation(pirp);
    code = stack->Parameters.DeviceIoControl.IoControlCode;
    length = stack->Parameters.DeviceIoControl.InputBufferLength;

    HLog("IRPIoControl Code = %X ���� = %d", code, length);

    switch (code) {
        case HCODE(0x803):
            
            break;
        default:
            break;
    }



    pirp->IoStatus.Status = STATUS_SUCCESS;
    pirp->IoStatus.Information = 4;
    IoCompleteRequest(pirp, IO_NO_INCREMENT);
    HLog("�뿪 IRPIoControl");
    return STATUS_SUCCESS;
}
