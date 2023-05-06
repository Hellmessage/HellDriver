#include "Hell.h"

NTSTATUS CreateDevice(PDRIVER_OBJECT pDriver) {
    HELL_PARAMS(pDriver);
    NTSTATUS status;
    UNICODE_STRING driver;
    PDEVICE_OBJECT device = NULL;
    RtlInitUnicodeString(&driver, HELL_DEVICE_NAME);
    status = IoCreateDevice(pDriver, sizeof(pDriver->DriverExtension), &driver, FILE_DEVICE_UNKNOWN, FILE_DEVICE_SECURE_OPEN, FALSE, &device);
    if (status == STATUS_SUCCESS) {
        HLog("驱动设备对象创建成功");
        UNICODE_STRING symbol;
        RtlInitUnicodeString(&symbol, HELL_SYMBOL_NAME);
        status = IoCreateSymbolicLink(&symbol, &driver);
        if (status == STATUS_SUCCESS) {
            HLog("符号创建<%wZ> 成功", &symbol);
            return status;
        } else {
            HLog("符号创建<%wZ> 失败,卸载设备 ErrorCode: %X", &symbol, status);
            if (device != NULL) {
                IoDeleteDevice(device);
            }
            return status;
        }
    } else {
        HLog("驱动设备对象创建失败,卸载设备");
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

        HLog("卸载符号 <%wZ>", &symbol);
        IoDeleteSymbolicLink(&symbol);

        HLog("卸载设备");
        IoDeleteDevice(pDriver->DeviceObject);
    }
}
