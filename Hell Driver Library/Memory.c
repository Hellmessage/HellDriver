#include "Memory.h"
#define DIRECTORY_TABLE_BASE	         0x028
#define HELL_32_CR3_OFF(dtb)             _disable();ULONG32 hell_o_cr3 = __readcr3();__writecr3(dtb);_enable()
#define HELL_64_CR3_OFF(dtb)             _disable();ULONG64 hell_o_cr3 = __readcr3();__writecr3(dtb);_enable()
#define HELL_CR3_ON()                    _disable();__writecr3(hell_o_cr3);_enable()
#define HELL_64_CR0_WP_OFF()             ULONG64 hell_o_cr0 = 0; KIRQL hell_cr0_irql = WP_CR0_OFF(&hell_o_cr0)
#define HELL_64_CR0_WP_ON()              WP_CR0_ON(hell_cr0_irql, hell_o_cr0)

ULONG64 Get64Bit(PVOID p);
ULONG32 Get32Bit(PVOID p);

KIRQL WP_CR0_OFF(OUT PULONG64 cr0);
void WP_CR0_ON(KIRQL irql, ULONG64 cr0);

UINT64 GetPhysicalMaxLength();
PVOID GetPhysicalAddress(UINT32 pid, PVOID address);
NTSTATUS ReadPhysicalMemory(PVOID physical, PVOID buffer, UINT32 length);
NTSTATUS WritePhysicalMemory(PVOID physical, PVOID buffer, UINT32 length);

BOOLEAN KReadProcessMemory(PEPROCESS process, PVOID address, PVOID buffer, UINT32 length);
BOOLEAN KReadProcessMemoryMDL(PEPROCESS process, PVOID address, PVOID buffer, UINT32 length);
BOOLEAN KReadProcessMemoryCR3(PEPROCESS process, PVOID address, PVOID buffer, UINT32 length);

BOOLEAN KWriteProcessMemoryMDL(PEPROCESS process, PVOID address, PVOID buffer, UINT32 length);
BOOLEAN KWriteProcessOnlyReadMemoryMDL(PEPROCESS process, PVOID address, PVOID buffer, UINT32 length);
BOOLEAN KWriteProcessOnlyReadMemoryCR0(PEPROCESS process, PVOID address, PVOID buffer, UINT32 length);

#pragma region ���ڴ�

NTSTATUS KReadProcessMemoryByPid(UINT32 pid, PVOID address, PVOID buffer, UINT32 length) {
    PEPROCESS pe = NULL;
    NTSTATUS status = PsLookupProcessByProcessId(((PVOID)((UINT_PTR)pid)), &pe);
    if (status != STATUS_SUCCESS) {
        return status;
    }
    BOOLEAN result = KReadProcessMemory(pe, address, buffer, length);
    ObDereferenceObject(pe);
    if (result) {
        return STATUS_SUCCESS;
    } else {
        return STATUS_UNSUCCESSFUL;
    }
}

NTSTATUS KReadProcessMemoryMDLByPid(UINT32 pid, PVOID address, PVOID buffer, UINT32 length) {
    PEPROCESS pe = NULL;
    NTSTATUS status = PsLookupProcessByProcessId(((PVOID)((UINT_PTR)pid)), &pe);
    if (status != STATUS_SUCCESS) {
        return status;
    }
    BOOLEAN result = KReadProcessMemoryMDL(pe, address, buffer, length);
    ObDereferenceObject(pe);
    if (result) {
        return STATUS_SUCCESS;
    } else {
        return STATUS_UNSUCCESSFUL;
    }
}

NTSTATUS KReadProcessMemoryCR3ByPid(UINT32 pid, PVOID address, PVOID buffer, UINT32 length) {
    PEPROCESS pe = NULL;
    NTSTATUS status = PsLookupProcessByProcessId(((PVOID)((UINT_PTR)pid)), &pe);
    if (status != STATUS_SUCCESS) {
        return status;
    }
    BOOLEAN result = KReadProcessMemoryCR3(pe, address, buffer, length);
    ObDereferenceObject(pe);
    if (result) {
        return STATUS_SUCCESS;
    } else {
        return STATUS_UNSUCCESSFUL;
    }
}

NTSTATUS KReadProcessPhysicalMemoryByPid(UINT32 pid, PVOID address, PVOID buffer, UINT32 length) {
    PVOID physical = GetPhysicalAddress(pid, address);
    if (physical == NULL) {
        HLog("��ȡ�����ַʧ��");
        return STATUS_UNSUCCESSFUL;
    }
    HLog("�����ַ: %p", physical);
    return ReadPhysicalMemory(physical, buffer, length);
}

#pragma endregion

#pragma region д�ڴ�

NTSTATUS KWriteProcessMemoryByPid(UINT32 pid, PVOID address, PVOID buffer, UINT32 length) {
    PEPROCESS pe = NULL;
    NTSTATUS status = PsLookupProcessByProcessId(((PVOID)((UINT_PTR)pid)), &pe);
    if (status != STATUS_SUCCESS) {
        return status;
    }
    BOOLEAN result = KWriteProcessMemoryMDL(pe, address, buffer, length);
    ObDereferenceObject(pe);
    if (result) {
        return STATUS_SUCCESS;
    } else {
        return STATUS_UNSUCCESSFUL;
    }
}

NTSTATUS KWriteProcessOnlyReadMemoryByPid(UINT32 pid, PVOID address, PVOID buffer, UINT32 length) {
    PEPROCESS pe = NULL;
    NTSTATUS status = PsLookupProcessByProcessId(((PVOID)((UINT_PTR)pid)), &pe);
    if (status != STATUS_SUCCESS) {
        return status;
    }
    BOOLEAN result = KWriteProcessOnlyReadMemoryMDL(pe, address, buffer, length);
    ObDereferenceObject(pe);
    if (result) {
        return STATUS_SUCCESS;
    } else {
        return STATUS_UNSUCCESSFUL;
    }
}

NTSTATUS KWriteProcessOnlyReadMemoryCR0ByPid(UINT32 pid, PVOID address, PVOID buffer, UINT32 length) {
    PEPROCESS pe = NULL;
    NTSTATUS status = PsLookupProcessByProcessId(((PVOID)((UINT_PTR)pid)), &pe);
    if (status != STATUS_SUCCESS) {
        return status;
    }
    BOOLEAN result = KWriteProcessOnlyReadMemoryCR0(pe, address, buffer, length);
    ObDereferenceObject(pe);
    if (result) {
        return STATUS_SUCCESS;
    } else {
        return STATUS_UNSUCCESSFUL;
    }
}

NTSTATUS KWriteProcessPhysicalMemoryByPid(UINT32 pid, PVOID address, PVOID buffer, UINT32 length) {
    PVOID physical = GetPhysicalAddress(pid, address);
    if (physical == NULL) {
        HLog("��ȡ�����ַʧ��");
        return STATUS_UNSUCCESSFUL;
    }
    HLog("�����ַ: %p", physical);
    return WritePhysicalMemory(physical, buffer, length);
}

#pragma endregion

#pragma region ���ڴ�

BOOLEAN KReadProcessMemory(PEPROCESS process, PVOID address, PVOID buffer, UINT32 length) {
    KAPC_STATE apc;
    RtlZeroMemory(&apc, sizeof(KAPC_STATE));
    PVOID temp = ExAllocatePool2(POOL_FLAG_NON_PAGED, length, 'kert');
    if (temp == NULL || !MmIsAddressValid(temp)) {
        HLog("����/���� �ں˿ռ�ʧ��!");
        return FALSE;
    }
    RtlZeroMemory(temp, length);
    KeStackAttachProcess((PVOID)process, &apc);//���ӵ����̿ռ�
    RtlCopyMemory(temp, address, length);
    KeUnstackDetachProcess(&apc);//������̿ռ�
    RtlCopyMemory(buffer, temp, length);
    ExFreePoolWithTag(temp, 'kert');
    return TRUE;
}

/// <summary>
/// KReadProcessMemoryCR3 ��ʵ���� KReadProcessMemory һ������
/// </summary>
BOOLEAN KReadProcessMemoryCR3(PEPROCESS process, PVOID address, PVOID buffer, UINT32 length) {
    ULONG64 dtb = Get64Bit((PCHAR)process + DIRECTORY_TABLE_BASE);
    if (dtb == 0L) {
        HLog("��ȡDTBʧ��");
        return FALSE;
    }
    HELL_64_CR3_OFF(dtb);
    BOOLEAN result = MmIsAddressValid(address);
    if (result) {
        RtlCopyMemory(buffer, address, length);
    }
    HELL_CR3_ON();
    return result;
}

BOOLEAN KReadProcessMemoryMDL(PEPROCESS process, PVOID address, PVOID buffer, UINT32 length) {
    KAPC_STATE apc;
    RtlZeroMemory(&apc, sizeof(KAPC_STATE));
    PMDL pmdl = IoAllocateMdl(buffer, length, FALSE, FALSE, NULL);
    if (pmdl == NULL) {
        return FALSE;
    }
    MmBuildMdlForNonPagedPool(pmdl);
    PUCHAR mapped = (PUCHAR)MmMapLockedPagesSpecifyCache(pmdl, KernelMode, MmCached, 0L, 0L, NormalPagePriority);
    if (mapped == NULL) {
        HLog("ӳ��MDLʧ��");
        IoFreeMdl(pmdl);
        return FALSE;
    }
    KeStackAttachProcess((PVOID)process, &apc);
    BOOLEAN result = MmIsAddressValid(address);
    if (result) {
        RtlCopyMemory(mapped, address, length);
    }
    KeUnstackDetachProcess(&apc);
    MmUnmapLockedPages((PVOID)mapped, pmdl);
    IoFreeMdl(pmdl);
    return result;
}

#pragma endregion

#pragma region д�ڴ�

BOOLEAN KWriteProcessMemoryMDL(PEPROCESS process, PVOID address, PVOID buffer, UINT32 length) {
    KAPC_STATE apc;
    RtlZeroMemory(&apc, sizeof(KAPC_STATE));
    PMDL pmdl = IoAllocateMdl(buffer, length, FALSE, FALSE, NULL);
    if (pmdl == NULL) {
        return FALSE;
    }
    MmBuildMdlForNonPagedPool(pmdl);
    PUCHAR mapped = (PUCHAR)MmMapLockedPagesSpecifyCache(pmdl, KernelMode, MmCached, 0L, 0L, NormalPagePriority);
    if (mapped == NULL) {
        HLog("ӳ��MDLʧ��");
        IoFreeMdl(pmdl);
        return FALSE;
    }
    KeStackAttachProcess((PVOID)process, &apc);
    BOOLEAN result = MmIsAddressValid(address);
    if (result) {
        RtlCopyMemory(address, mapped, length);
    }
    KeUnstackDetachProcess(&apc);
    MmUnmapLockedPages((PVOID)mapped, pmdl);
    IoFreeMdl(pmdl);
    return result;
}

BOOLEAN KWriteProcessOnlyReadMemoryMDL(PEPROCESS process, PVOID address, PVOID buffer, UINT32 length) {
    KAPC_STATE apc;
    RtlZeroMemory(&apc, sizeof(KAPC_STATE));
    KeStackAttachProcess((PVOID)process, &apc);
    BOOLEAN result = MmIsAddressValid(address);
    if (!result) {
        KeUnstackDetachProcess(&apc);
        return FALSE;
    }
    PMDL pmdl = IoAllocateMdl(address, length, FALSE, FALSE, NULL);
    if (pmdl == NULL) {
        KeUnstackDetachProcess(&apc);
        return FALSE;
    }
    MmBuildMdlForNonPagedPool(pmdl);
    pmdl->MdlFlags = MDL_WRITE_OPERATION | MDL_ALLOCATED_FIXED_SIZE | MDL_PAGES_LOCKED;
    PUCHAR mapped = (PUCHAR)MmMapLockedPagesSpecifyCache(pmdl, KernelMode, MmCached, 0L, 0L, NormalPagePriority);
    KeUnstackDetachProcess(&apc);
    if (mapped == NULL) {
        HLog("ӳ��MDLʧ��");
        IoFreeMdl(pmdl);
        return FALSE;
    }
    RtlCopyMemory(mapped, buffer, length);
    MmUnmapLockedPages((PVOID)mapped, pmdl);
    IoFreeMdl(pmdl);
    return result;
}

BOOLEAN KWriteProcessOnlyReadMemoryCR0(PEPROCESS process, PVOID address, PVOID buffer, UINT32 length) {
    KAPC_STATE apc;
    RtlZeroMemory(&apc, sizeof(KAPC_STATE));
    KeStackAttachProcess((PVOID)process, &apc);
    BOOLEAN result = MmIsAddressValid(address);
    if (!result) {
        KeUnstackDetachProcess(&apc);
        return FALSE;
    }
    PMDL pmdl = IoAllocateMdl(address, length, FALSE, FALSE, NULL);
    if (pmdl == NULL) {
        KeUnstackDetachProcess(&apc);
        return FALSE;
    }
    MmBuildMdlForNonPagedPool(pmdl);
    PUCHAR mapped = (PUCHAR)MmMapLockedPagesSpecifyCache(pmdl, KernelMode, MmCached, 0L, 0L, NormalPagePriority);
    KeUnstackDetachProcess(&apc);
    if (mapped == NULL) {
        HLog("ӳ��MDLʧ��");
        IoFreeMdl(pmdl);
        return FALSE;
    }
    /*ULONG64 cr0 = 0; KIRQL irql = WP_CR0_OFF(&cr0);*/
    HELL_64_CR0_WP_OFF();
    RtlCopyMemory(mapped, buffer, length);
    HELL_64_CR0_WP_ON();
    //WP_CR0_ON(irql, cr0);
    MmUnmapLockedPages((PVOID)mapped, pmdl);
    IoFreeMdl(pmdl);
    return result;
}

#pragma endregion

#pragma region �����ڴ����

ULONG64 g_PhysicalMaxLength = 0;
ULONG64 GetPhysicalMaxLength() {
    if (g_PhysicalMaxLength == 0) {
        INT physical;
        INT32 r[4];
        __cpuid(r, 0x80000008);
        physical = r[0] & 0xFF;
        g_PhysicalMaxLength = 0xFFFFFFFFFFFFFFFF;
        g_PhysicalMaxLength >>= physical;
        g_PhysicalMaxLength = ~(g_PhysicalMaxLength << physical);
    }
    return g_PhysicalMaxLength;
}

PVOID GetPhysicalAddress(UINT32 pid, PVOID address) {
    PEPROCESS pe = null;
    PHYSICAL_ADDRESS physical;
    physical.QuadPart = 0;
    NTSTATUS status = PsLookupProcessByProcessId(((PVOID)((UINT_PTR)pid)), &pe);
    if (status != STATUS_SUCCESS) {
        return NULL;
    }
    KAPC_STATE apc;
    RtlZeroMemory(&apc, sizeof(KAPC_STATE));
    KeStackAttachProcess((PVOID)pe, &apc);
    __try {
        physical = MmGetPhysicalAddress(address);
    }
    __finally {
        KeUnstackDetachProcess(&apc);
        ObDereferenceObject(pe);
    }
    return (PVOID)physical.QuadPart;
}

NTSTATUS ReadPhysicalMemory(PVOID physical, PVOID buffer, UINT32 length) {
    HANDLE physmen = NULL;
    UNICODE_STRING physmenString = { 0 };
    OBJECT_ATTRIBUTES attr = { 0 };
    PWCHAR physmemName = L"\\device\\physicalmemory";
    PUCHAR vaddress = NULL;
    NTSTATUS status = STATUS_UNSUCCESSFUL;

    if ((ULONG64)physical > GetPhysicalMaxLength() || ((ULONG64)physical + length) > GetPhysicalMaxLength()) {
        HLog("����Խ��");
        return status;
    }
    PMDL pmdl = IoAllocateMdl(buffer, length, FALSE, FALSE, NULL);
    if (pmdl == NULL) {
        return status;
    }
    __try {
        MmProbeAndLockPages(pmdl, KernelMode, IoWriteAccess);
    }
    __except (1) {
        IoFreeMdl(pmdl);
        return status;
    }
    RtlInitUnicodeString(&physmenString, physmemName);
    InitializeObjectAttributes(&attr, &physmenString, OBJ_CASE_INSENSITIVE, NULL, NULL);
    status = ZwOpenSection(&physmen, SECTION_ALL_ACCESS, &attr);
    if (status == STATUS_SUCCESS) {
        SIZE_T size = 0x2000;
        PHYSICAL_ADDRESS base = { 0 };
        base.QuadPart = (ULONG64)physical;
        UINT_PTR offset;
        UINT_PTR toread = length;

        status = ZwMapViewOfSection(physmen, NtCurrentProcess(), &vaddress, 0L, size, &base, &size, ViewShare, 0, PAGE_READWRITE);
        if (status == STATUS_SUCCESS && vaddress != NULL) {
            if (toread > size) {
                toread = size;
            }
            if (toread) {
                offset = (UINT_PTR)physical - (UINT_PTR)base.QuadPart;
                if (offset + toread > size) {
                    __noop(("Error Խ��"));
                } else {
                    RtlCopyMemory(buffer, &vaddress[offset], toread);
                }
                ZwUnmapViewOfSection(NtCurrentProcess(), vaddress);
            }
        }
        ZwClose(physmen);
    }
    MmUnlockPages(pmdl);
    IoFreeMdl(pmdl);
    return status;
}

NTSTATUS WritePhysicalMemory(PVOID physical, PVOID buffer, UINT32 length) {
    HANDLE physmen = NULL;
    UNICODE_STRING physmenString = { 0 };
    OBJECT_ATTRIBUTES attr = { 0 };
    PWCHAR physmemName = L"\\device\\physicalmemory";
    PUCHAR vaddress = NULL;
    NTSTATUS status = STATUS_UNSUCCESSFUL;

    if ((ULONG64)physical > GetPhysicalMaxLength() || ((ULONG64)physical + length) > GetPhysicalMaxLength()) {
        HLog("����Խ��");
        return status;
    }
    PMDL pmdl = IoAllocateMdl(buffer, length, FALSE, FALSE, NULL);
    if (pmdl == NULL) {
        return status;
    }
    __try {
        MmProbeAndLockPages(pmdl, KernelMode, IoWriteAccess);
    } __except (1) {
        IoFreeMdl(pmdl);
        return status;
    }
    RtlInitUnicodeString(&physmenString, physmemName);
    InitializeObjectAttributes(&attr, &physmenString, OBJ_CASE_INSENSITIVE, NULL, NULL);
    status = ZwOpenSection(&physmen, SECTION_ALL_ACCESS, &attr);
    if (status == STATUS_SUCCESS) {
        SIZE_T size = 0x2000;
        PHYSICAL_ADDRESS base = { 0 };
        base.QuadPart = (ULONG64)physical;
        UINT_PTR offset;
        UINT_PTR toread = length;

        status = ZwMapViewOfSection(physmen, NtCurrentProcess(), &vaddress, 0L, size, &base, &size, ViewShare, 0, PAGE_READWRITE);
        if (status == STATUS_SUCCESS && vaddress != NULL) {
            if (toread > size) {
                toread = size;
            }
            if (toread) {
                offset = (UINT_PTR)physical - (UINT_PTR)base.QuadPart;
                if (offset + toread > size) {
                    __noop(("Error Խ��"));
                } else {
                    RtlCopyMemory(&vaddress[offset], buffer, toread);
                }
                ZwUnmapViewOfSection(NtCurrentProcess(), vaddress);
            }
        }
        ZwClose(physmen);
    }
    MmUnlockPages(pmdl);
    IoFreeMdl(pmdl);
    return status;
}


#pragma endregion

#pragma region д����CR0

KIRQL WP_CR0_OFF(OUT PULONG64 cr0) {
    KIRQL irql = KeRaiseIrqlToDpcLevel();
    ULONG64 tcr0 = __readcr0();
    *cr0 = tcr0;
    tcr0 &= 0xFFFFFFFFFFFEFFFF;
    __writecr0(tcr0);
    _disable();
    HLog("CR0 OLD:%llu NEW:%llu", *cr0, tcr0);
    return irql;
}

void WP_CR0_ON(KIRQL irql, ULONG64 cr0) {
    _enable();
    __writecr0(cr0);
    KeLowerIrql(irql);
}

#pragma endregion

#pragma region ��ȡ�ж�
ULONG32 Get32Bit(PVOID p) {
#ifdef _X86_
    if (MmIsAddressValid(p) == FALSE) {
        return 0;
    }
    return *(PULONG32)p;
#else
    p;
    return 0;
#endif // _X86_
}

ULONG64 Get64Bit(PVOID p) {
#ifdef _AMD64_
    if (MmIsAddressValid(p) == FALSE) {
        return 0;
    }
    return *(PULONG64)p;
#else
    p;
    return 0;
#endif // _ARM64_
}
#pragma endregion