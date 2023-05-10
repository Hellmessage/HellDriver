#ifndef __HELL_PROCESS_HEADER__
#define __HELL_PROCESS_HEADER__

#include "Hell.h"

NTSTATUS ProcessGetObjectByHandle(IN HANDLE handle, OUT POBJECT_HANDLE_INFORMATION object);


#endif // !__HELL_PROCESS_HEADER__
