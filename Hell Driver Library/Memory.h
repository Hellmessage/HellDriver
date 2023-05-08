#ifndef __HELL_MEMORY_HEADER__
#define __HELL_MEMORY_HEADER__

#include "Hell.h"

NTSTATUS KReadProcessMemoryByPid(UINT32 pid, PVOID address, PVOID buffer, UINT32 length);
NTSTATUS KReadProcessMemoryMDLByPid(UINT32 pid, PVOID address, PVOID buffer, UINT32 length);
NTSTATUS KReadProcessMemoryCR3ByPid(UINT32 pid, PVOID address, PVOID buffer, UINT32 length);
NTSTATUS KReadProcessPhysicalMemoryByPid(UINT32 pid, PVOID address, PVOID buffer, UINT32 length);


NTSTATUS KWriteProcessMemoryByPid(UINT32 pid, PVOID address, PVOID buffer, UINT32 length);
NTSTATUS KWriteProcessOnlyReadMemoryByPid(UINT32 pid, PVOID address, PVOID buffer, UINT32 length);
NTSTATUS KWriteProcessOnlyReadMemoryCR0ByPid(UINT32 pid, PVOID address, PVOID buffer, UINT32 length);
NTSTATUS KWriteProcessPhysicalMemoryByPid(UINT32 pid, PVOID address, PVOID buffer, UINT32 length);

#endif // !__HELL_MEMORY_HEADER__
