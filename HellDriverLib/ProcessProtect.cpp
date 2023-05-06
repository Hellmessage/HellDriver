#include "HellDriver.h"

void StartProtectProcess() {
    HANDLE driver = GetDriver();
    if (driver == NULL) {
        return;
    }
    LPDWORD outSize = 0;
    DeviceIoControl(driver, CODE_LOAD_SSDTHOOK, NULL, 0, NULL, 0, outSize, (LPOVERLAPPED)NULL);
}

void StopProtectProcess() {
    HANDLE driver = GetDriver();
    if (driver == NULL) {
        return;
    }
    LPDWORD outSize = 0;
    DeviceIoControl(driver, CODE_UNLOAD_SSDTHOOK, NULL, 0, NULL, 0, outSize, (LPOVERLAPPED)NULL);
}

BOOLEAN ProtectProcess(UINT32 pid, ACCESS_MASK access) {
    HANDLE driver = GetDriver();
    if (driver == NULL) {
        return FALSE;
    }
    PProtectProcessItem item = (PProtectProcessItem)malloc(sizeof(ProtectProcessItem));
    if (item == NULL) {
        return FALSE;
    }
    item->ProcessId = pid;
    item->ExcludeAccess = access;
    DWORD outSize = 0;
    DeviceIoControl(driver, CODE_IN_SSDT_PROTECT, item, sizeof(ProtectProcessItem), NULL, 0, &outSize, (LPOVERLAPPED)NULL);
    free(item);
    return TRUE;
}

BOOLEAN UnProtectProcess(UINT32 pid) {
    HANDLE driver = GetDriver();
    if (driver == NULL) {
        return FALSE;
    }
    PProtectProcessItem item = (PProtectProcessItem)malloc(sizeof(ProtectProcessItem));
    if (item == NULL) {
        return FALSE;
    }
    item->ProcessId = pid;
    item->ExcludeAccess = 0;
    DWORD outSize = 0;
    DeviceIoControl(driver, CODE_UN_SSDT_PROTECT, item, sizeof(ProtectProcessItem), NULL, 0, &outSize, (LPOVERLAPPED)NULL);
    free(item);
    return TRUE;
}