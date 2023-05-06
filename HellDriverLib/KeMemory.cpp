#include "KeMemory.h"
#include "HellDriver.h"

UINT32 KeProcessMemoryOpt(DWORD code, UINT32 pid, UINT64 address, PVOID buffer, UINT32 length);


UINT32 KeProcessMemoryRead(UINT32 pid, UINT64 address, PVOID buffer, UINT32 length) {
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
        DeviceIoControl(driver, IO_CODE_KE_MEMORY_READ, opt, sizeof(ProcessMemoryOpt), buffer, length, &outSize, (LPOVERLAPPED)NULL);
        free(opt);
    }
    return outSize;
}

UINT32 KeProcessMemoryMDLRead(UINT32 pid, UINT64 address, PVOID buffer, UINT32 length) {
    /*HANDLE driver = GetDriver();
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
        DeviceIoControl(driver, IO_CODE_KE_MEMORY_MDL_READ, opt, sizeof(ProcessMemoryOpt), NULL, 0, &outSize, (LPOVERLAPPED)NULL);
        free(opt);
    }
    return outSize;*/
    return KeProcessMemoryOpt(IO_CODE_KE_MEMORY_MDL_READ, pid, address, buffer, length);
}

UINT32 KeProcessMemoryCR3Read(UINT32 pid, UINT64 address, PVOID buffer, UINT32 length) {
    /*HANDLE driver = GetDriver();
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
        DeviceIoControl(driver, IO_CODE_KE_MEMORY_CR3_READ, opt, sizeof(ProcessMemoryOpt), NULL, 0, &outSize, (LPOVERLAPPED)NULL);
        free(opt);
    }
    return outSize;*/
    return KeProcessMemoryOpt(IO_CODE_KE_MEMORY_CR3_READ, pid, address, buffer, length);
}

UINT32 KeProcessMemoryWrite(UINT32 pid, UINT64 address, PVOID buffer, UINT32 length) {
    /*HANDLE driver = GetDriver();
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
        DeviceIoControl(driver, IO_CODE_KE_MEMORY_WRITE, opt, sizeof(ProcessMemoryOpt), NULL, 0, &outSize, (LPOVERLAPPED)NULL);
        free(opt);
    }
    return outSize;*/
    return KeProcessMemoryOpt(IO_CODE_KE_MEMORY_WRITE, pid, address, buffer, length);
}

UINT32 KeProcessOnlyReadMemoryWrite(UINT32 pid, UINT64 address, PVOID buffer, UINT32 length) {
    //HANDLE driver = GetDriver();
    //if (driver == NULL) {
    //    return -1;
    //}
    //DWORD outSize = 0;
    //PProcessMemoryOpt opt = (PProcessMemoryOpt)malloc(sizeof(ProcessMemoryOpt));
    //if (opt != NULL) {
    //    opt->ProcessId = pid;
    //    opt->Address = address;
    //    opt->Length = length;
    //    opt->UserBuffer = buffer;
    //    DeviceIoControl(driver, IO_CODE_KE_MEMORY_WRITE_ONLYREAD, opt, sizeof(ProcessMemoryOpt), NULL, 0, &outSize, (LPOVERLAPPED)NULL);
    //    free(opt);
    //}
    //return outSize;
    return KeProcessMemoryOpt(IO_CODE_KE_MEMORY_WRITE_ONLYREAD, pid, address, buffer, length);
}

UINT32 KeProcessOnlyReadMemoryCR0Write(UINT32 pid, UINT64 address, PVOID buffer, UINT32 length) {
    //HANDLE driver = GetDriver();
    //if (driver == NULL) {
    //    return -1;
    //}
    //DWORD outSize = 0;
    //PProcessMemoryOpt opt = (PProcessMemoryOpt)malloc(sizeof(ProcessMemoryOpt));
    //if (opt != NULL) {
    //    opt->ProcessId = pid;
    //    opt->Address = address;
    //    opt->Length = length;
    //    opt->UserBuffer = buffer;
    //    DeviceIoControl(driver, IO_CODE_KE_MEMORY_WRITE_ONLYREAD_CR0, opt, sizeof(ProcessMemoryOpt), NULL, 0, &outSize, (LPOVERLAPPED)NULL);
    //    free(opt);
    //}
    return KeProcessMemoryOpt(IO_CODE_KE_MEMORY_WRITE_ONLYREAD_CR0, pid, address, buffer, length);
}

UINT32 KeProcessMemoryOpt(DWORD code, UINT32 pid, UINT64 address, PVOID buffer, UINT32 length) {
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
        DeviceIoControl(driver, code, opt, sizeof(ProcessMemoryOpt), NULL, 0, &outSize, (LPOVERLAPPED)NULL);
        free(opt);
    }
    return outSize;
}
