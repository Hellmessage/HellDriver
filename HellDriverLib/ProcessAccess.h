#ifndef __HELL_PROCESS_ACCESS_HOOK_HEADER__
#define __HELL_PROCESS_ACCESS_HOOK_HEADER__

#include "Hell.h"

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

    HELLCALL void ProcessAccessInstall();
    HELLCALL void ProcessAccessUninstall();
    HELLCALL BOOLEAN ProcessAccessSetHook(UINT32 pid, UINT32 type, ACCESS_MASK access);
    HELLCALL BOOLEAN ProcessAccessDelHook(UINT32 pid);

#ifdef __cplusplus
}
#endif // __cplusplus




#endif // !__HELL_PROCESS_ACCESS_HOOK_HEADER__
