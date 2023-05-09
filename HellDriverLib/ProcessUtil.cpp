#include "HTools.h"

void ElevatePrivileges() {
    HANDLE token = NULL;
    if (OpenProcessToken(GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &token)) {
        TOKEN_PRIVILEGES tp;
        tp.PrivilegeCount = 1;
        tp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;
        LookupPrivilegeValue(NULL, SE_DEBUG_NAME, &tp.Privileges[0].Luid);
        AdjustTokenPrivileges(token, FALSE, &tp, 0, (PTOKEN_PRIVILEGES)NULL, 0);
        CloseHandle(token);
    }
}

BOOLEAN EnumProcessHandle(EnumProcessHandleEvent event) {
    ElevatePrivileges();

    SYSTEM_HANDLE_INFORMATION temp;
    ULONG size = 0;
    NTSTATUS status = NtQuerySystemInformation(SYSTEM_INFORMATION_CLASS::SystemHandleInformation, &temp, sizeof(SYSTEM_HANDLE_INFORMATION), &size);
    if (status != STATUS_INFO_LENGTH_MISMATCH) {
        return FALSE;
    }

    HLOCAL buffer = LocalAlloc(0, size);
    if (buffer == NULL) {
        return FALSE;
    }

    PSYSTEM_HANDLE_INFORMATION handles = (PSYSTEM_HANDLE_INFORMATION)LocalLock(buffer);
    if (handles == NULL) {
        LocalFree(buffer);
        return FALSE;
    }

    memset(handles, 0, size);
    status = NtQuerySystemInformation(SYSTEM_INFORMATION_CLASS::SystemHandleInformation, handles, size, &size);
    if (status != STATUS_SUCCESS) {
        LocalFree(buffer);
        return EnumProcessHandle(event);
    }

    POBJECT_NAME_INFORMATION name = (POBJECT_NAME_INFORMATION)malloc(4196);
    if (name == NULL) {
        LocalFree(buffer);
        return FALSE;
    }

    POBJECT_NAME_INFORMATION type = (POBJECT_NAME_INFORMATION)malloc(1024);
    if (type == NULL) {
        free(name);
        LocalFree(buffer);
        return FALSE;
    }

    for (ULONG i = 0; i < handles->NumberOfHandles; i++) {
        HANDLE handle = NULL;
        HANDLE pipeHandle;
        DWORD flags1 = 0;
        DWORD flags2 = 0;
        HANDLE process = OpenProcess(PROCESS_ALL_ACCESS, FALSE, handles->Handles[i].ProcessId);
        if (process == NULL) {
            continue;
        }
        DuplicateHandle(
            process,
            (HANDLE)handles->Handles[i].Handle,
            GetCurrentProcess(),
            &handle,
            DUPLICATE_SAME_ACCESS,
            FALSE,
            DUPLICATE_SAME_ACCESS);
        if (handle != NULL) {
            pipeHandle = CreateFileMapping(handle, NULL, PAGE_READONLY, 0, 1024, L"HellFileMapTest");
            if (pipeHandle == NULL) {
                if (GetLastError() == 193) {
                    continue;
                }
            }
            status = NtQueryObject(handle, OBJECT_INFORMATION_CLASS::ObjectTypeInformation, type, 128, &flags2);
            if (status == STATUS_SUCCESS) {
                status = NtQueryObject(handle, OBJECT_INFORMATION_CLASS::ObjectNameInformation, name, 4196, &flags1);
                if (status == STATUS_SUCCESS) {
                    event(type->Name, name->Name, handles->Handles[i], handle);
                }
            }
            if (pipeHandle != NULL) {
                CloseHandle(pipeHandle);
            }
            CloseHandle(handle);
        }
        CloseHandle(process);
    }
    free(name);
    free(type);
    LocalFree(buffer);
    HLog("¹²ÓÐ¾ä±úÊý: %d", size);
    return TRUE;
}

DWORD HandleToProcessId(HANDLE process) {
    PROCESS_BASIC_INFORMATION pbi = { 0 };
    NTSTATUS status = NtQueryInformationProcess(process, PROCESSINFO_CLASS::ProcessBasicInformation, &pbi, sizeof(PROCESS_BASIC_INFORMATION), NULL);
    if (status == STATUS_SUCCESS) {
        return (DWORD)(UINT_PTR)pbi.UniqueProcessId;
    }
    return 0;
}
