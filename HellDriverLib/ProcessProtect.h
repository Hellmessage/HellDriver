#ifndef __HELL_PROCESS_PROTECT_HEADER__
#define __HELL_PROCESS_PROTECT_HEADER__

#include "Hell.h"

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

    HELLCALL void StartProtectProcess();
    HELLCALL void StopProtectProcess();

    HELLCALL BOOLEAN ProtectProcess(UINT32 pid, ACCESS_MASK access);
    HELLCALL BOOLEAN UnProtectProcess(UINT32 pid);

#ifdef __cplusplus
}
#endif // __cplusplus




#endif // !__HELL_PROCESS_PROTECT_HEADER__


