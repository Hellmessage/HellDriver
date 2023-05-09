#ifndef __HELL_PROCESS_UTIL_HEADER__
#define __HELL_PROCESS_UTIL_HEADER__

#include "Hell.h"

typedef void(EnumProcessHandleEvent)(UNICODE_STRING type, UNICODE_STRING name, SYSTEM_HANDLE_TABLE_ENTRY_INFO info, HANDLE handle);

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

    HELLCALL void ElevatePrivileges();
    HELLCALL BOOLEAN EnumProcessHandle(EnumProcessHandleEvent event);
    HELLCALL DWORD HandleToProcessId(HANDLE process);



#ifdef __cplusplus
}
#endif // __cplusplus


#endif // !__HELL_PROCESS_UTIL_HEADER__
