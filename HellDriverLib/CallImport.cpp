#include "HTools.h"

typedef NTSTATUS(WINAPI* NTDLL_NtQuerySystemInformation) (SYSTEM_INFORMATION_CLASS SystemInformationClass, PVOID SystemInformation, ULONG SystemInformationLength, PULONG pReturnLength);
typedef NTSTATUS(WINAPI* NTDLL_NtQueryObject)(HANDLE Handle, OBJECT_INFORMATION_CLASS Info, PVOID Buffer, ULONG BufferSize, PULONG ReturnLength);
typedef NTSTATUS(WINAPI* NTDLL_NtQueryInformationFile)(HANDLE Handle, PIO_STATUS_BLOCK IO, PVOID Ptr, ULONG Length, FILE_INFORMATION_CLASS Cls);
typedef NTSTATUS(WINAPI* NTDLL_NtQueryInformationProcess)(HANDLE ProcessHandle, PROCESSINFO_CLASS ProcessInformationClass, PVOID ProcessInformation, ULONG ProcessInformationLength, PULONG ReturnLength);


PVOID GetDllProc(LPCWCH dll, LPCCH name) {
    HMODULE module = LoadLibrary(dll);
    if (module == NULL) {
        return NULL;
    }
    return GetProcAddress(module, name);
}

NTSTATUS NtQuerySystemInformation(SYSTEM_INFORMATION_CLASS SystemInformationClass, PVOID SystemInformation, ULONG SystemInformationLength, PULONG pReturnLength) {
    static NTDLL_NtQuerySystemInformation func = NULL;
    if (func == NULL) {
        func = (NTDLL_NtQuerySystemInformation)GetDllProc(L"ntdll.dll", "NtQuerySystemInformation");
        if (func == NULL) {
            return STATUS_UNSUCCESSFUL;
        }
    }
    return func(SystemInformationClass, SystemInformation, SystemInformationLength, pReturnLength);
}

NTSTATUS NtQueryObject(HANDLE Handle, OBJECT_INFORMATION_CLASS Info, PVOID Buffer, ULONG BufferSize, PULONG ReturnLength) {
    static NTDLL_NtQueryObject func = NULL;
    if (func == NULL) {
        func = (NTDLL_NtQueryObject)GetDllProc(L"ntdll.dll", "NtQueryObject");
        if (func == NULL) {
            return STATUS_UNSUCCESSFUL;
        }
    }
    return func(Handle, Info, Buffer, BufferSize, ReturnLength);
}

NTSTATUS NtQueryInformationFile(HANDLE Handle, PIO_STATUS_BLOCK IO, PVOID Ptr, ULONG Length, FILE_INFORMATION_CLASS Cls) {
    static NTDLL_NtQueryInformationFile func = NULL;
    if (func == NULL) {
        func = (NTDLL_NtQueryInformationFile)GetDllProc(L"ntdll.dll", "NtQueryInformationFile");
        if (func == NULL) {
            return STATUS_UNSUCCESSFUL;
        }
    }
    return func(Handle, IO, Ptr, Length, Cls);
}

NTSTATUS NtQueryInformationProcess(HANDLE ProcessHandle, PROCESSINFO_CLASS ProcessInformationClass, PVOID ProcessInformation, ULONG ProcessInformationLength, PULONG ReturnLength) {
    static NTDLL_NtQueryInformationProcess func = NULL;
    if (func == NULL) {
        func = (NTDLL_NtQueryInformationProcess)GetDllProc(L"ntdll.dll", "NtQueryInformationProcess");
        if (func == NULL) {
            return STATUS_UNSUCCESSFUL;
        }
    }
    return func(ProcessHandle, ProcessInformationClass, ProcessInformation, ProcessInformationLength, ReturnLength);
}