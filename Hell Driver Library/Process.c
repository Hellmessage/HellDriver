#include "SSDT.h"
#include "Process.h"

NTSTATUS ProcessGetObjectByHandle(IN HANDLE handle, OUT POBJECT_HANDLE_INFORMATION object) {
    HELL_PARAMS(handle);
    NTSTATUS status = STATUS_UNSUCCESSFUL;
    status = ObReferenceObjectByHandle(handle, PROCESS_ALL_ACCESS, *PsProcessType, KernelMode, (PVOID)object, object);
    HLog("ObReferenceObjectByHandle:  %d", status);
    if (status == STATUS_SUCCESS) {
        HLog("ªÒ»°≥…!!!");
    }

    return status;
}

