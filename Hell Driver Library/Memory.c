#include "Memory.h"
BOOLEAN KReadProcessMemory(PEPROCESS process, PVOID address, UINT32 length, PVOID buffer);
BOOLEAN KReadProcessMemoryMDL(PEPROCESS process, PVOID address, UINT32 length, PVOID buffer);
BOOLEAN KWriteProcessMemoryMDL(PEPROCESS process, PVOID address, UINT32 length, PVOID buffer);

NTSTATUS KReadProcessMemoryByPid(UINT32 pid, PVOID address, UINT32 length, PVOID buffer) {
    PEPROCESS pe = NULL;
    NTSTATUS status = PsLookupProcessByProcessId(((PVOID)((UINT_PTR)pid)), &pe);
    if (status != STATUS_SUCCESS) {
        return status;
    }
    BOOLEAN result = KReadProcessMemory(pe, address, length, buffer);
    ObDereferenceObject(pe);
    if (result) {
        return STATUS_SUCCESS;
    } else {
        return STATUS_UNSUCCESSFUL;
    }
}

NTSTATUS KReadProcessMemoryMDLByPid(UINT32 pid, PVOID address, UINT32 length, PVOID buffer) {
    PEPROCESS pe = NULL;
    NTSTATUS status = PsLookupProcessByProcessId(((PVOID)((UINT_PTR)pid)), &pe);
    if (status != STATUS_SUCCESS) {
        return status;
    }
    BOOLEAN result = KReadProcessMemoryMDL(pe, address, length, buffer);
    ObDereferenceObject(pe);
    if (result) {
        return STATUS_SUCCESS;
    } else {
        return STATUS_UNSUCCESSFUL;
    }
}

NTSTATUS KWriteProcessMemoryByPid(UINT32 pid, PVOID address, UINT32 length, PVOID buffer) {
    PEPROCESS pe = NULL;
    NTSTATUS status = PsLookupProcessByProcessId(((PVOID)((UINT_PTR)pid)), &pe);
    if (status != STATUS_SUCCESS) {
        return status;
    }
    BOOLEAN result = KWriteProcessMemoryMDL(pe, address, length, buffer);
    ObDereferenceObject(pe);
    if (result) {
        return STATUS_SUCCESS;
    } else {
        return STATUS_UNSUCCESSFUL;
    }
}

BOOLEAN KReadProcessMemoryMDL(PEPROCESS process, PVOID address, UINT32 length, PVOID buffer) {
    KAPC_STATE apc;
    RtlZeroMemory(&apc, sizeof(KAPC_STATE));
    PMDL pmdl = IoAllocateMdl(buffer, length, 0, 0, NULL);
    if (pmdl == NULL) {
        return FALSE;
    }
    MmBuildMdlForNonPagedPool(pmdl);
    //PUCHAR mapped = (PUCHAR)MmMapLockedPages(pmdl, KernelMode);
    PUCHAR mapped = (PUCHAR)MmMapLockedPagesSpecifyCache(pmdl, KernelMode, MmCached, 0L, 0L, NormalPagePriority);
    if (mapped == NULL) {
        HLog("映射MDL失败");
        IoFreeMdl(pmdl);
        return FALSE;
    }
    KeStackAttachProcess((PVOID)process, &apc);//附加到进程空间
    BOOLEAN result = MmIsAddressValid(address);
    if (result) {
        RtlCopyMemory(mapped, address, length);
    }
    KeUnstackDetachProcess(&apc);//分离进程空间
    MmUnmapLockedPages((PVOID)mapped, pmdl);
    IoFreeMdl(pmdl);
    return result;
}

BOOLEAN KReadProcessMemory(PEPROCESS process, PVOID address, UINT32 length, PVOID buffer) {
    KAPC_STATE apc;
    RtlZeroMemory(&apc, sizeof(KAPC_STATE));
    PVOID temp = ExAllocatePool2(POOL_FLAG_NON_PAGED, length, 'kert');
    if (temp == NULL || !MmIsAddressValid(temp)) {
        HLog("申请/访问 内核空间失败!");
        return FALSE;
    }
    KeStackAttachProcess((PVOID)process, &apc);//附加到进程空间
    RtlCopyMemory(temp, address, length);
    KeUnstackDetachProcess(&apc);//分离进程空间
    RtlCopyMemory(buffer, temp, length);
    ExFreePoolWithTag(temp, 'kert');
    return TRUE;
}

BOOLEAN KWriteProcessMemoryMDL(PEPROCESS process, PVOID address, UINT32 length, PVOID buffer) {
    KAPC_STATE apc;
    RtlZeroMemory(&apc, sizeof(KAPC_STATE));
    PMDL pmdl = IoAllocateMdl(buffer, length, 0, 0, NULL);
    if (pmdl == NULL) {
        return FALSE;
    }
    MmBuildMdlForNonPagedPool(pmdl);
    //PUCHAR mapped = (PUCHAR)MmMapLockedPages(pmdl, KernelMode);
    PUCHAR mapped = (PUCHAR)MmMapLockedPagesSpecifyCache(pmdl, KernelMode, MmCached, 0L, 0L, NormalPagePriority);
    if (mapped == NULL) {
        HLog("映射MDL失败");
        IoFreeMdl(pmdl);
        return FALSE;
    }
    KeStackAttachProcess((PVOID)process, &apc);//附加到进程空间
    BOOLEAN result = MmIsAddressValid(address);
    if (result) {
        RtlCopyMemory(address, mapped, length);
    }
    KeUnstackDetachProcess(&apc);//分离进程空间
    MmUnmapLockedPages((PVOID)mapped, pmdl);
    IoFreeMdl(pmdl);
    return result;
}
