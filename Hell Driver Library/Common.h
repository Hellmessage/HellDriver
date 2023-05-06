#ifndef __HELL_COMMON_HEADER__
#define __HELL_COMMON_HEADER__

#define HELL_DEVICE_NAME                       L"\\DEVICE\\HellDriver"
#define HELL_SYMBOL_NAME                       L"\\??\\HellDriver"

#ifdef HELL_DRIVER
#include <ntifs.h>
#else
#include <Windows.h>
#include <winioctl.h>
#endif // HELL_DRIVER

#define HCODE(code)                     CTL_CODE(FILE_DEVICE_UNKNOWN, code, METHOD_BUFFERED, FILE_ANY_ACCESS)

#define CODE_WRITE                  HCODE(0x803)
#define CODE_READ                   HCODE(0x804)
#define CODE_READ_WRITE             HCODE(0x805)


#pragma region 进程保护

#define CODE_LOAD_SSDTHOOK          HCODE(0x806)
#define CODE_UNLOAD_SSDTHOOK        HCODE(0x807)
#define CODE_IN_SSDT_PROTECT        HCODE(0x808)
#define CODE_UN_SSDT_PROTECT        HCODE(0x809)

#pragma endregion



typedef struct _protect_process_item {
    UINT32          ProcessId;
    ACCESS_MASK     ExcludeAccess;
    LIST_ENTRY      ListEntry;
} ProtectProcessItem, * PProtectProcessItem;



#endif // !__HELL_COMMON_HEADER__