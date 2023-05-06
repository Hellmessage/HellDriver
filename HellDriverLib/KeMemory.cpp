#include "KeMemory.h"
#include "HellDriver.h"

UINT32 KeProcessMemoryRead(UINT32 pid, UINT64 address, PVOID buffer, UINT32 length) {
    HANDLE driver = GetDriver();
    if (driver == NULL) {
        return -1;
    }
    PProcessMemoryOpt opt = (PProcessMemoryOpt)malloc(sizeof(ProcessMemoryOpt));
    if (opt != NULL) {
        opt->ProcessId = pid;
        opt->Address = address;
        opt->Length = length;
        DWORD outSize = 0;
        DeviceIoControl(driver, CODE_KE_READ_MEMORY, opt, sizeof(ProcessMemoryOpt), buffer, length, &outSize, (LPOVERLAPPED)NULL);
        free(opt);
        return outSize;
    }
    return -1;
}

UINT32 KeProcessMemoryMDLRead(UINT32 pid, UINT64 address, PVOID buffer, UINT32 length) {
    HANDLE driver = GetDriver();
    if (driver == NULL) {
        return -1;
    }
    DWORD outSize = 0;
    PProcessMemoryOpt opt = (PProcessMemoryOpt)malloc(sizeof(ProcessMemoryOpt));
    if (opt != NULL) {
        opt->ProcessId = pid;
        opt->Address = address;
        opt->Length = length;
        opt->UserBuffer = buffer;
        DeviceIoControl(driver, CODE_KE_READ_MEMORY_MDL, opt, sizeof(ProcessMemoryOpt), NULL, 0, &outSize, (LPOVERLAPPED)NULL);
        free(opt);
    }
    return outSize;
}

UINT32 KeProcessMemoryWrite(UINT32 pid, UINT64 address, PVOID buffer, UINT32 length) {
    HANDLE driver = GetDriver();
    if (driver == NULL) {
        return -1;
    }
    DWORD outSize = 0;
    PProcessMemoryOpt opt = (PProcessMemoryOpt)malloc(sizeof(ProcessMemoryOpt));
    if (opt != NULL) {
        opt->ProcessId = pid;
        opt->Address = address;
        opt->Length = length;
        opt->UserBuffer = buffer;
        DeviceIoControl(driver, CODE_KE_WRITE_MEMORY, opt, sizeof(ProcessMemoryOpt), NULL, 0, &outSize, (LPOVERLAPPED)NULL);
        free(opt);
    }
    return outSize;
}
