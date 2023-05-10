#ifndef __HELL_PROCESS_ACCESS_HEADER__
#define __HELL_PROCESS_ACCESS_HEADER__

#include "Hell.h"

NTSTATUS ProcessAccessHookInstall();
NTSTATUS ProcessAccessHookUninstall();

BOOLEAN ProcessAccessSetHook(PHELL_PROCESS_ACCESS_OPT opt);
BOOLEAN ProcessAccessDelHook(PHELL_PROCESS_ACCESS_OPT opt);
void ProcessAccessClear();

#endif // !__HELL_PROCESS_ACCESS_HEADER__
