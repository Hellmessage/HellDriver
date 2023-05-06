#include "Hell.h"

NTSTATUS CreateDevice(PDRIVER_OBJECT pDriver) {
    HELL_PARAMS(pDriver);
    NTSTATUS status;
    UNICODE_STRING driver;
    PDEVICE_OBJECT device = NULL;
    RtlInitUnicodeString(&driver, HELL_DEVICE_NAME);
    status = IoCreateDevice(pDriver, sizeof(pDriver->DriverExtension), &driver, FILE_DEVICE_UNKNOWN, FILE_DEVICE_SECURE_OPEN, FALSE, &device);
    if (status == STATUS_SUCCESS) {
        HLog("�����豸���󴴽��ɹ�");
        UNICODE_STRING symbol;
        RtlInitUnicodeString(&symbol, HELL_SYMBOL_NAME);
        status = IoCreateSymbolicLink(&symbol, &driver);
        if (status == STATUS_SUCCESS) {
            HLog("���Ŵ���<%wZ> �ɹ�", &symbol);
            return status;
        } else {
            HLog("���Ŵ���<%wZ> ʧ��,ж���豸 ErrorCode: %X", &symbol, status);
            if (device != NULL) {
                IoDeleteDevice(device);
            }
            return status;
        }
    } else {
        HLog("�����豸���󴴽�ʧ��,ж���豸");
        if (device != NULL) {
            IoDeleteDevice(device);
        }
    }
    return status;
}

void DeleteDevice(PDRIVER_OBJECT pDriver) {
    if (pDriver->DeviceObject) {
        UNICODE_STRING symbol;
        RtlInitUnicodeString(&symbol, HELL_SYMBOL_NAME);

        HLog("ж�ط��� <%wZ>", &symbol);
        IoDeleteSymbolicLink(&symbol);

        HLog("ж���豸");
        IoDeleteDevice(pDriver->DeviceObject);
    }
}
