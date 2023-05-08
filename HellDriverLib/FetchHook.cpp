#include "HellDriver.h"

void GetFetchHook() {
    HANDLE driver = GetDriver();
    if (driver == NULL) {
        return;
    }
    LPDWORD outSize = 0;
    DeviceIoControl(driver, IO_CODE_FETCH_HOOK, NULL, 0, NULL, 0, outSize, (LPOVERLAPPED)NULL);
}
