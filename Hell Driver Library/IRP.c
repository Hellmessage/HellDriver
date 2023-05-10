#include "Hell.h"
#include "Memory.h"
#include "SSDT.h"

void TestHandle(PIRP pirp, PIO_STACK_LOCATION stack);


void ProcessAccessSetHookEx(PIRP pirp, PIO_STACK_LOCATION stack);
void ProcessAccessDelHookEx(PIRP pirp, PIO_STACK_LOCATION stack);

UINT32 KEProcessMemoryRead(PIRP pirp, PIO_STACK_LOCATION stack);
UINT32 KEProcessMemoryMDLRead(PIRP pirp, PIO_STACK_LOCATION stack);
UINT32 KEProcessMemoryCR3Read(PIRP pirp, PIO_STACK_LOCATION stack);
UINT32 KEProcessPhysicalMemoryRead(PIRP pirp, PIO_STACK_LOCATION stack);

UINT32 KEProcessMemoryMDLWrite(PIRP pirp, PIO_STACK_LOCATION stack);
UINT32 KEProcessOnlyReadMemoryMDLWrite(PIRP pirp, PIO_STACK_LOCATION stack);
UINT32 KEProcessOnlyReadMemoryCR0Write(PIRP pirp, PIO_STACK_LOCATION stack);
UINT32 KEProcessPhysicalMemory(PIRP pirp, PIO_STACK_LOCATION stack);

NTSTATUS IRPHandle(PDEVICE_OBJECT pDevice, PIRP pirp) {
    HELL_PARAMS(pDevice);
    HELL_PARAMS(pirp);

    HLog("进入 IRP 派遣");
    PIO_STACK_LOCATION stack;
    stack = IoGetCurrentIrpStackLocation(pirp);
    switch (stack->MajorFunction) {
        case IRP_MJ_CREATE:
            HLog("派遣 IRP_MJ_CREATE");
            break;
        case IRP_MJ_CLOSE:
            HLog("派遣 IRP_MJ_CLOSE");
            break;
        default:
            HLog("派遣 IRP = %X", stack->MajorFunction);
            break;
    }
    pirp->IoStatus.Status = STATUS_SUCCESS;
    pirp->IoStatus.Information = 4;
    IoCompleteRequest(pirp, IO_NO_INCREMENT);
    HLog("离开IRP");
    return STATUS_SUCCESS;
}

NTSTATUS IRPIoControl(PDEVICE_OBJECT pDevice, PIRP pirp) {
    HLog("进入 IRPIoControl");
    HELL_PARAMS(pDevice);
    HELL_PARAMS(pirp);
    
    PIO_STACK_LOCATION stack;
    ULONG code;
    stack = IoGetCurrentIrpStackLocation(pirp);
    code = stack->Parameters.DeviceIoControl.IoControlCode;
    HLog("IRPIoControl Code = %X", code);

    pirp->IoStatus.Status = STATUS_SUCCESS;
    pirp->IoStatus.Information = 4;

    switch (code) {
        case IO_CODE_PROCESS_ACCESS_HOOK_INSTALL:
            ProcessAccessHookInstall();
            break;
        case IO_CODE_PROCESS_ACCESS_HOOK_UNINSTALL:
            ProcessAccessHookUninstall();
            break;
        case IO_CODE_PROCESS_ACCESS_HOOK_SET:
            ProcessAccessSetHookEx(pirp, stack);
            break;
        case IO_CODE_PROCESS_ACCESS_HOOK_DEL:
            ProcessAccessDelHookEx(pirp, stack);
            break;

        case IO_CODE_FETCH_HOOK:
            EnumRegisterHookCallBacks();
            break;
        case IO_CODE_PROCESS_GET_OBJECT_HANDLE:
            TestHandle(pirp, stack);
            break;

        case IO_CODE_KE_MEMORY_READ:
            pirp->IoStatus.Information = KEProcessMemoryRead(pirp, stack);
            break;
        case IO_CODE_KE_MEMORY_READ_MDL:
            pirp->IoStatus.Information = KEProcessMemoryMDLRead(pirp, stack);
            break;
        case IO_CODE_KE_MEMORY_READ_CR3:
            pirp->IoStatus.Information = KEProcessMemoryCR3Read(pirp, stack);
            break;
        case IO_CODE_KE_MEMORY_READ_PHYSICAL:
            pirp->IoStatus.Information = KEProcessPhysicalMemoryRead(pirp, stack);
            break;
        case IO_CODE_KE_MEMORY_WRITE:
            pirp->IoStatus.Information = KEProcessMemoryMDLWrite(pirp, stack);
            break;
        case IO_CODE_KE_MEMORY_WRITE_ONLYREAD:
            pirp->IoStatus.Information = KEProcessOnlyReadMemoryMDLWrite(pirp, stack);
            break;
        case IO_CODE_KE_MEMORY_WRITE_ONLYREAD_CR0:
            pirp->IoStatus.Information = KEProcessOnlyReadMemoryCR0Write(pirp, stack);
            break;
        case IO_CODE_KE_MEMORY_WRITE_PHYSICAL:
            pirp->IoStatus.Information = KEProcessPhysicalMemory(pirp, stack);
        default:
            break;
    }
    IoCompleteRequest(pirp, IO_NO_INCREMENT);
    HLog("离开 IRPIoControl");
    return STATUS_SUCCESS;
}




void TestHandle(PIRP pirp, PIO_STACK_LOCATION stack) {
    HELL_PARAMS(pirp);
    HELL_PARAMS(stack);
    HANDLE handle = (HANDLE)(*(ULONG64*)pirp->AssociatedIrp.SystemBuffer);
    OBJECT_HANDLE_INFORMATION obj = { 0 };
    ProcessGetObjectByHandle(handle, &obj);
}






























#pragma region 内存保护相关

void ProcessAccessSetHookEx(PIRP pirp, PIO_STACK_LOCATION stack) {
    HELL_PARAMS(pirp);
    HELL_PARAMS(stack);
    ULONG length = sizeof(HELL_PROCESS_ACCESS_OPT);
    PHELL_PROCESS_ACCESS_OPT opt = (PHELL_PROCESS_ACCESS_OPT)ExAllocatePool2(POOL_FLAG_NON_PAGED, length, 'temp');
    if (opt != NULL) {
        RtlZeroMemory(opt, length);
        RtlCopyMemory(opt, pirp->AssociatedIrp.SystemBuffer, length);
        ProcessAccessSetHook(opt);
        ExFreePoolWithTag(opt, 'temp');
    }
}

void ProcessAccessDelHookEx(PIRP pirp, PIO_STACK_LOCATION stack) {
    HELL_PARAMS(pirp);
    HELL_PARAMS(stack);
    ULONG length = sizeof(HELL_PROCESS_ACCESS_OPT);
    PHELL_PROCESS_ACCESS_OPT opt = (PHELL_PROCESS_ACCESS_OPT)ExAllocatePool2(POOL_FLAG_NON_PAGED, length, 'temp');
    if (opt != NULL) {
        RtlZeroMemory(opt, length);
        RtlCopyMemory(opt, pirp->AssociatedIrp.SystemBuffer, length);
        ProcessAccessDelHook(opt);
        ExFreePoolWithTag(opt, 'temp');
    }
}

#pragma endregion

#pragma region 内存读写

UINT32 KEProcessMemoryRead(PIRP pirp, PIO_STACK_LOCATION stack) {
    HELL_PARAMS(pirp);
    HELL_PARAMS(stack);
    UINT32 readLen = 0;
    ULONG length = sizeof(ProcessMemoryOpt);
    PProcessMemoryOpt opt = (PProcessMemoryOpt)ExAllocatePool2(POOL_FLAG_NON_PAGED, length, 'opt');
    if (opt != NULL && MmIsAddressValid(opt)) {
        RtlZeroMemory(opt, length);
        RtlCopyMemory(opt, pirp->AssociatedIrp.SystemBuffer, length);
        PVOID buffer = ExAllocatePool2(POOL_FLAG_NON_PAGED, opt->Length, 'buf');
        if (buffer == NULL) {
            ExFreePoolWithTag(opt, 'opt');
            pirp->IoStatus.Status = STATUS_UNSUCCESSFUL;
        } else {
            NTSTATUS status = KReadProcessMemoryByPid((UINT32)opt->ProcessId, (PVOID)opt->Address, buffer, opt->Length);
            pirp->IoStatus.Status = status;
            if (status == STATUS_SUCCESS) {
                RtlCopyMemory(pirp->AssociatedIrp.SystemBuffer, buffer, opt->Length);
                readLen = opt->Length;
                UNICODE_STRING str;
                RtlInitUnicodeString(&str, (PCWSTR)buffer);
                HLog("读出数据: %wZ", str);
                ExFreePoolWithTag(buffer, 'buf');
                ExFreePoolWithTag(opt, 'opt');
            }
        }
    } else {
        pirp->IoStatus.Status = STATUS_UNSUCCESSFUL;
    }
    return readLen;
}

UINT32 KEProcessMemoryMDLRead(PIRP pirp, PIO_STACK_LOCATION stack) {
    HELL_PARAMS(pirp);
    HELL_PARAMS(stack);
    UINT32 readLen = 0;
    ULONG length = sizeof(ProcessMemoryOpt);
    PProcessMemoryOpt opt = (PProcessMemoryOpt)ExAllocatePool2(POOL_FLAG_NON_PAGED, length, 'opt');
    if (opt != NULL && MmIsAddressValid(opt)) {
        RtlZeroMemory(opt, length);
        RtlCopyMemory(opt, pirp->AssociatedIrp.SystemBuffer, length);
        NTSTATUS status = KReadProcessMemoryMDLByPid((UINT32)opt->ProcessId, (PVOID)opt->Address, opt->UserBuffer, opt->Length);
        pirp->IoStatus.Status = status;
        if (status == STATUS_SUCCESS) {
            readLen = opt->Length;
            UNICODE_STRING str;
            RtlInitUnicodeString(&str, (PCWSTR)opt->UserBuffer);
            HLog("读出数据: %wZ", str);
            ExFreePoolWithTag(opt, 'opt');
        }
    } else {
        pirp->IoStatus.Status = STATUS_UNSUCCESSFUL;
    }
    return readLen;
}

UINT32 KEProcessMemoryCR3Read(PIRP pirp, PIO_STACK_LOCATION stack) {
    HELL_PARAMS(pirp);
    HELL_PARAMS(stack);
    UINT32 readLen = 0;
    ULONG length = sizeof(ProcessMemoryOpt);
    PProcessMemoryOpt opt = (PProcessMemoryOpt)ExAllocatePool2(POOL_FLAG_NON_PAGED, length, 'opt');
    if (opt != NULL && MmIsAddressValid(opt)) {
        RtlZeroMemory(opt, length);
        RtlCopyMemory(opt, pirp->AssociatedIrp.SystemBuffer, length);
        PVOID buffer = ExAllocatePool2(POOL_FLAG_NON_PAGED, opt->Length, 'buf');
        if (buffer == NULL) {
            ExFreePoolWithTag(opt, 'opt');
            pirp->IoStatus.Status = STATUS_UNSUCCESSFUL;
        } else {
            NTSTATUS status = KReadProcessMemoryCR3ByPid((UINT32)opt->ProcessId, (PVOID)opt->Address, buffer, opt->Length);
            pirp->IoStatus.Status = status;
            if (status == STATUS_SUCCESS) {
                RtlCopyMemory(pirp->AssociatedIrp.SystemBuffer, buffer, opt->Length);
                readLen = opt->Length;
                UNICODE_STRING str;
                RtlInitUnicodeString(&str, (PCWSTR)buffer);
                HLog("读出数据CR3: %wZ", str);
                ExFreePoolWithTag(buffer, 'buf');
                ExFreePoolWithTag(opt, 'opt');
            }
        }
    } else {
        pirp->IoStatus.Status = STATUS_UNSUCCESSFUL;
    }
    return readLen;
}

UINT32 KEProcessPhysicalMemoryRead(PIRP pirp, PIO_STACK_LOCATION stack) {
    HELL_PARAMS(pirp);
    HELL_PARAMS(stack);
    UINT32 readLen = 0;
    ULONG length = sizeof(ProcessMemoryOpt);
    PProcessMemoryOpt opt = (PProcessMemoryOpt)ExAllocatePool2(POOL_FLAG_NON_PAGED, length, 'opt');
    if (opt != NULL && MmIsAddressValid(opt)) {
        RtlZeroMemory(opt, length);
        RtlCopyMemory(opt, pirp->AssociatedIrp.SystemBuffer, length);
        NTSTATUS status = KReadProcessPhysicalMemoryByPid((UINT32)opt->ProcessId, (PVOID)opt->Address, opt->UserBuffer, opt->Length);
        pirp->IoStatus.Status = status;
        if (status == STATUS_SUCCESS) {
            readLen = opt->Length;
            UNICODE_STRING str;
            RtlInitUnicodeString(&str, (PCWSTR)opt->UserBuffer);
            HLog("读出数据Physical: %wZ", str);
            ExFreePoolWithTag(opt, 'opt');
        }
    } else {
        pirp->IoStatus.Status = STATUS_UNSUCCESSFUL;
    }
    return readLen;
}

UINT32 KEProcessMemoryMDLWrite(PIRP pirp, PIO_STACK_LOCATION stack) {
    HELL_PARAMS(pirp);
    HELL_PARAMS(stack);
    UINT32 readLen = 0;
    ULONG length = sizeof(ProcessMemoryOpt);
    PProcessMemoryOpt opt = (PProcessMemoryOpt)ExAllocatePool2(POOL_FLAG_NON_PAGED, length, 'opt');
    if (opt != NULL && MmIsAddressValid(opt)) {
        RtlZeroMemory(opt, length);
        RtlCopyMemory(opt, pirp->AssociatedIrp.SystemBuffer, length);
        NTSTATUS status = KWriteProcessMemoryByPid((UINT32)opt->ProcessId, (PVOID)opt->Address, opt->UserBuffer, opt->Length);
        pirp->IoStatus.Status = status;
        if (status == STATUS_SUCCESS) {
            readLen = opt->Length;
            HLog("写入内存");
            ExFreePoolWithTag(opt, 'opt');
        }
    } else {
        pirp->IoStatus.Status = STATUS_UNSUCCESSFUL;
    }
    return readLen;
}

UINT32 KEProcessOnlyReadMemoryMDLWrite(PIRP pirp, PIO_STACK_LOCATION stack) {
    HELL_PARAMS(pirp);
    HELL_PARAMS(stack);
    UINT32 readLen = 0;
    ULONG length = sizeof(ProcessMemoryOpt);
    PProcessMemoryOpt opt = (PProcessMemoryOpt)ExAllocatePool2(POOL_FLAG_NON_PAGED, length, 'opt');
    if (opt != NULL && MmIsAddressValid(opt)) {
        RtlZeroMemory(opt, length);
        RtlCopyMemory(opt, pirp->AssociatedIrp.SystemBuffer, length);
        NTSTATUS status = KWriteProcessOnlyReadMemoryByPid((UINT32)opt->ProcessId, (PVOID)opt->Address, opt->UserBuffer, opt->Length);
        pirp->IoStatus.Status = status;
        if (status == STATUS_SUCCESS) {
            readLen = opt->Length;
            HLog("写入内存");
            ExFreePoolWithTag(opt, 'opt');
        }
    } else {
        pirp->IoStatus.Status = STATUS_UNSUCCESSFUL;
    }
    return readLen;
}

UINT32 KEProcessOnlyReadMemoryCR0Write(PIRP pirp, PIO_STACK_LOCATION stack) {
    HELL_PARAMS(pirp);
    HELL_PARAMS(stack);
    UINT32 readLen = 0;
    ULONG length = sizeof(ProcessMemoryOpt);
    PProcessMemoryOpt opt = (PProcessMemoryOpt)ExAllocatePool2(POOL_FLAG_NON_PAGED, length, 'opt');
    if (opt != NULL && MmIsAddressValid(opt)) {
        RtlZeroMemory(opt, length);
        RtlCopyMemory(opt, pirp->AssociatedIrp.SystemBuffer, length);
        NTSTATUS status = KWriteProcessOnlyReadMemoryCR0ByPid((UINT32)opt->ProcessId, (PVOID)opt->Address, opt->UserBuffer, opt->Length);
        pirp->IoStatus.Status = status;
        if (status == STATUS_SUCCESS) {
            readLen = opt->Length;
            HLog("写入内存");
            ExFreePoolWithTag(opt, 'opt');
        }
    } else {
        pirp->IoStatus.Status = STATUS_UNSUCCESSFUL;
    }
    return readLen;
}

UINT32 KEProcessPhysicalMemory(PIRP pirp, PIO_STACK_LOCATION stack) {
    HELL_PARAMS(pirp);
    HELL_PARAMS(stack);
    UINT32 readLen = 0;
    ULONG length = sizeof(ProcessMemoryOpt);
    PProcessMemoryOpt opt = (PProcessMemoryOpt)ExAllocatePool2(POOL_FLAG_NON_PAGED, length, 'opt');
    if (opt != NULL && MmIsAddressValid(opt)) {
        RtlZeroMemory(opt, length);
        RtlCopyMemory(opt, pirp->AssociatedIrp.SystemBuffer, length);
        NTSTATUS status = KWriteProcessPhysicalMemoryByPid((UINT32)opt->ProcessId, (PVOID)opt->Address, opt->UserBuffer, opt->Length);
        pirp->IoStatus.Status = status;
        if (status == STATUS_SUCCESS) {
            readLen = opt->Length;
            HLog("写入内存Physical");
            ExFreePoolWithTag(opt, 'opt');
        }
    } else {
        pirp->IoStatus.Status = STATUS_UNSUCCESSFUL;
    }
    return readLen;
}

#pragma endregion