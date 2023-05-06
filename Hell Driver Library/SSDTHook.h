#ifndef __HELL_SSDT_HOOK_HEADER__
#define __HELL_SSDT_HOOK_HEADER__

#include "Hell.h"

NTSTATUS LoadSSDTHook();
void UnloadSSDTHook();

void FreeSSDTProtect();
void AddSSDTProtect(UINT32 pid, ACCESS_MASK access);
void RemoveSSDTProtect(UINT32 pid);

#endif // !__HELL_SSDT_HOOK_HEADER__
