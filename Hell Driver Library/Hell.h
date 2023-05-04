#ifndef __HELL_HEADER__
#define __HELL_HEADER__

#define HELL_DRIVER
#include "Common.h"

#define null                            NULL
#define HELL_PARAMS(name)               (name)
#define HLog(format, ...)               DbgPrint("R0 Hell: "#format, __VA_ARGS__)

NTSTATUS CreateDevice(PDRIVER_OBJECT pDriver);
void DeleteDevice(PDRIVER_OBJECT pDriver);

void UnloadDriver(PDRIVER_OBJECT pDriver);
NTSTATUS IRPHandle(PDEVICE_OBJECT pDevice, PIRP pirp);
NTSTATUS IRPIoControl(PDEVICE_OBJECT pDevice, PIRP pirp);

#endif // !__HELL_HEADER__