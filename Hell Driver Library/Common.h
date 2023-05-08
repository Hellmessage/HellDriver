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

#define HCODE(code)                                         CTL_CODE(FILE_DEVICE_UNKNOWN, code, METHOD_BUFFERED, FILE_ANY_ACCESS)

#define IO_CODE_WRITE                                       HCODE(0x803)
#define IO_CODE_READ                                        HCODE(0x804)
#define IO_CODE_READ_WRITE                                  HCODE(0x805)

#pragma region 进程保护
#define IO_CODE_FETCH_HOOK                                  HCODE(0x80F)

#define IO_CODE_PROCESS_ACCESS_HOOK_INSTALL                 HCODE(0x900)
#define IO_CODE_PROCESS_ACCESS_HOOK_UNINSTALL               HCODE(0x901)
#define IO_CODE_PROCESS_ACCESS_HOOK_SET                     HCODE(0x902)
#define IO_CODE_PROCESS_ACCESS_HOOK_DEL                     HCODE(0x903)

#pragma endregion

#pragma region 过进程保护读写
#define IO_CODE_KE_MEMORY_READ                              HCODE(0x810)
#define IO_CODE_KE_MEMORY_READ_MDL                          HCODE(0x811)
#define IO_CODE_KE_MEMORY_READ_CR3                          HCODE(0x812)
#define IO_CODE_KE_MEMORY_READ_PHYSICAL                     HCODE(0x81A)
#define IO_CODE_KE_MEMORY_WRITE                             HCODE(0x813)
#define IO_CODE_KE_MEMORY_WRITE_ONLYREAD                    HCODE(0x814)
#define IO_CODE_KE_MEMORY_WRITE_ONLYREAD_CR0                HCODE(0x815)
#define IO_CODE_KE_MEMORY_WRITE_PHYSICAL                    HCODE(0x816)
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


#define HPAT_ENHANCE                       0x1
#define HPAT_REDUCE                        0x2
#define HPAT_PROTECT                       0x4
#define HPAT_MAINTAIN                      0x8

typedef struct _HELL_PROCESS_ACCESS_OPT {
    UINT32          ProcessId;
    UINT32          AccessType;
    ACCESS_MASK     Access;
} HELL_PROCESS_ACCESS_OPT, * PHELL_PROCESS_ACCESS_OPT;

#endif // !__HELL_COMMON_HEADER__