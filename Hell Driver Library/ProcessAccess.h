#ifndef __HELL_PROCESS_ACCESS_HEADER__
#define __HELL_PROCESS_ACCESS_HEADER__

#include "Hell.h"

NTSTATUS ProcessAccessHookInstall();
NTSTATUS ProcessAccessHookUninstall();


void ProcessAccessSetHook(PHELL_PROCESS_ACCESS_OPT opt);
void ProcessAccessDelHook(PHELL_PROCESS_ACCESS_OPT opt);
void ProcessAccessClear();

#endif // !__HELL_PROCESS_ACCESS_HEADER__
