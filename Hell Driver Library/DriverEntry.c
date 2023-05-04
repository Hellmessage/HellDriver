#include "Hell.h"

NTSTATUS DriverEntry(_In_ PDRIVER_OBJECT pDriver, _In_ PUNICODE_STRING path) {
    HLog("��������<%wZ>", path);

    HELL_PARAMS(pDriver);
    HELL_PARAMS(path);
    pDriver->DriverUnload = UnloadDriver;

    NTSTATUS status = CreateDevice(pDriver);
    if (status == STATUS_SUCCESS) {
        HLog("�������سɹ�, װ��IRP");
        pDriver->MajorFunction[IRP_MJ_CREATE] = IRPHandle;
        pDriver->MajorFunction[IRP_MJ_CLOSE] = IRPHandle;
        pDriver->MajorFunction[IRP_MJ_DEVICE_CONTROL] = IRPIoControl;
    }

    return status;
}

void UnloadDriver(PDRIVER_OBJECT pDriver) {
    HLog("ж�ؿ�ʼ");
    DeleteDevice(pDriver);
    HLog("ж�����");
}