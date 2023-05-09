#ifndef __HELL_CALL_IMPORT_HEADER__
#define __HELL_CALL_IMPORT_HEADER__

#include "Hell.h"
#include "Struct.h"

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

    HELLCALL PVOID GetDllProc(LPCWCH dll, LPCCH name);

    HELLCALL NTSTATUS NtQuerySystemInformation(SYSTEM_INFORMATION_CLASS SystemInformationClass, PVOID SystemInformation, ULONG SystemInformationLength, PULONG pReturnLength);
    HELLCALL NTSTATUS NtQueryObject(HANDLE Handle, OBJECT_INFORMATION_CLASS Info, PVOID Buffer, ULONG BufferSize, PULONG ReturnLength);
    HELLCALL NTSTATUS NtQueryInformationFile(HANDLE Handle, PIO_STATUS_BLOCK IO, PVOID Ptr, ULONG Length, FILE_INFORMATION_CLASS Cls);
    HELLCALL NTSTATUS NtQueryInformationProcess(HANDLE ProcessHandle, PROCESSINFO_CLASS ProcessInformationClass, PVOID ProcessInformation, ULONG ProcessInformationLength, PULONG ReturnLength);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // !__HELL_CALL_IMPORT_HEADER__
