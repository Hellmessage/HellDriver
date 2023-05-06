#ifndef __HELL_MEMORY_HEADER__
#define __HELL_MEMORY_HEADER__

#include "Hell.h"

NTSTATUS KReadProcessMemoryByPid(UINT32 pid, PVOID address, UINT32 length, PVOID buffer);
NTSTATUS KReadProcessMemoryMDLByPid(UINT32 pid, PVOID address, UINT32 length, PVOID buffer);

NTSTATUS KWriteProcessMemoryByPid(UINT32 pid, PVOID address, UINT32 length, PVOID buffer);


#endif // !__HELL_MEMORY_HEADER__
