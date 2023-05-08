#include "HellDriver.h"

void ProcessAccessInstall() {
    HANDLE driver = GetDriver();
    if (driver == NULL) {
        return;
    }
    DWORD outSize = 0;
    DeviceIoControl(driver, IO_CODE_PROCESS_ACCESS_HOOK_INSTALL, NULL, 0, NULL, 0, &outSize, (LPOVERLAPPED)NULL);
}

void ProcessAccessUninstall() {
    HANDLE driver = GetDriver();
    if (driver == NULL) {
        return;
    }
    DWORD outSize = 0;
    DeviceIoControl(driver, IO_CODE_PROCESS_ACCESS_HOOK_UNINSTALL, NULL, 0, NULL, 0, &outSize, (LPOVERLAPPED)NULL);
}

BOOLEAN ProcessAccessSetHook(UINT32 pid, UINT32 type, ACCESS_MASK access) {
    HANDLE driver = GetDriver();
    if (driver == NULL) {
        return FALSE;
    }
    PHELL_PROCESS_ACCESS_OPT item = (PHELL_PROCESS_ACCESS_OPT)malloc(sizeof(HELL_PROCESS_ACCESS_OPT));
    if (item == NULL) {
        return FALSE;
    }
    item->ProcessId = pid;
    item->AccessType = type;
    item->Access = access;
    DWORD outSize = 0;
    DeviceIoControl(driver, IO_CODE_PROCESS_ACCESS_HOOK_SET, item, sizeof(HELL_PROCESS_ACCESS_OPT), NULL, 0, &outSize, (LPOVERLAPPED)NULL);
    free(item);
    return TRUE;
}

BOOLEAN ProcessAccessDelHook(UINT32 pid) {
    HANDLE driver = GetDriver();
    if (driver == NULL) {
        return FALSE;
    }
    PHELL_PROCESS_ACCESS_OPT item = (PHELL_PROCESS_ACCESS_OPT)malloc(sizeof(HELL_PROCESS_ACCESS_OPT));
    if (item == NULL) {
        return FALSE;
    }
    item->ProcessId = pid;
    item->AccessType = 0;
    item->Access = 0;
    DWORD outSize = 0;
    DeviceIoControl(driver, IO_CODE_PROCESS_ACCESS_HOOK_DEL, item, sizeof(HELL_PROCESS_ACCESS_OPT), NULL, 0, &outSize, (LPOVERLAPPED)NULL);
    free(item);
    return TRUE;
}
