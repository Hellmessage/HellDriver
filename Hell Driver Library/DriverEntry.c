#include "Hell.h"
#include "SSDT.h"

NTSTATUS DriverEntry(_In_ PDRIVER_OBJECT pDriver, _In_ PUNICODE_STRING path) {
    HLog("��������<%wZ>", path);

    HELL_PARAMS(pDriver);
    HELL_PARAMS(path);
    pDriver->DriverUnload = UnloadDriver;

    PLDR_DATA pld;
    pld = (PLDR_DATA)pDriver->DriverSection;
    pld->Flags |= 0x20;

    NTSTATUS status = CreateDevice(pDriver);
    if (status == STATUS_SUCCESS) {
        HLog("�������سɹ�, װ��IRP");
        pDriver->MajorFunction[IRP_MJ_CREATE] = IRPHandle;
        pDriver->MajorFunction[IRP_MJ_CLOSE] = IRPHandle;
        pDriver->MajorFunction[IRP_MJ_DEVICE_CONTROL] = IRPIoControl;


        EnumRegisterHookCallBacks();
    }
    return status;
}

void UnloadDriver(PDRIVER_OBJECT pDriver) {
    HLog("ж�ؿ�ʼ");

    
    ProcessAccessHookUninstall();
    
    DeleteDevice(pDriver);

    HLog("ж�����");
}