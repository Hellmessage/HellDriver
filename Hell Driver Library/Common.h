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

#define IO_CODE_WRITE                                       HCODE(0x803)
#define IO_CODE_READ                                        HCODE(0x804)
#define IO_CODE_READ_WRITE                                  HCODE(0x805)

#pragma region 进程保护
#define IO_CODE_LOAD_SSDTHOOK                               HCODE(0x806)
#define IO_CODE_UNLOAD_SSDTHOOK                             HCODE(0x807)
#define IO_CODE_IN_SSDT_PROTECT                             HCODE(0x808)
#define IO_CODE_UN_SSDT_PROTECT                             HCODE(0x809)
#pragma endregion

#pragma region 过进程保护读写
#define IO_CODE_KE_MEMORY_READ                              HCODE(0x810)
#define IO_CODE_KE_MEMORY_MDL_READ                          HCODE(0x811)
#define IO_CODE_KE_MEMORY_CR3_READ                          HCODE(0x812)
#define IO_CODE_KE_MEMORY_WRITE                             HCODE(0x813)
#define IO_CODE_KE_MEMORY_WRITE_ONLYREAD                    HCODE(0x814)
#define IO_CODE_KE_MEMORY_WRITE_ONLYREAD_CR0                HCODE(0x815)
#pragma endregion



typedef struct _protect_process_item {
    UINT32          ProcessId;
    ACCESS_MASK     ExcludeAccess;
    LIST_ENTRY      ListEntry;
} ProtectProcessItem, * PProtectProcessItem;

typedef struct _ke_process_memory_opt {
    UINT64          ProcessId;
    UINT64          Address;
    UINT32          Length;
    PVOID           UserBuffer;
} ProcessMemoryOpt, * PProcessMemoryOpt;

#endif // !__HELL_COMMON_HEADER__