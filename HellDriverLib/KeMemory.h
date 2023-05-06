#ifndef __HELL_KEMEMORY_HEADER__
#define __HELL_KEMEMORY_HEADER__

#include "Hell.h"



#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

    HELLCALL UINT32 KeProcessMemoryRead(UINT32 pid, UINT64 address, PVOID buffer, UINT32 length);
    HELLCALL UINT32 KeProcessMemoryMDLRead(UINT32 pid, UINT64 address, PVOID buffer, UINT32 length);
    HELLCALL UINT32 KeProcessMemoryWrite(UINT32 pid, UINT64 address, PVOID buffer, UINT32 length);
#ifdef __cplusplus
}
#endif // __cplusplus

#endif // !__HELL_KEMEMORY_HEADER__
