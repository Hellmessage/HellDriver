#ifndef __HELL_DRIVER_HEADER__
#define __HELL_DRIVER_HEADER__

#include "Hell.h"
#include "KeMemory.h"
#include "ProcessProtect.h"

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus
    HELLCALL int InstallDriver(LPCTSTR name, LPCTSTR path);
    HELLCALL void UninstallDriver(LPCTSTR name);

    HELLCALL void OpenDriver(LPCTSTR symbol);
    HELLCALL void CloseDriver();
    HELLCALL HANDLE GetDriver();
#ifdef __cplusplus
}
#endif // __cplusplus

#endif // !__HELL_DRIVER_HEADER__
