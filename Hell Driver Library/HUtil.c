#include "HUtil.h"

PUCHAR GetProcessNameByPid(HANDLE pid) {
    NTSTATUS st = STATUS_UNSUCCESSFUL;
    PEPROCESS pobj = NULL;
    PUCHAR name = NULL;
    st = PsLookupProcessByProcessId(pid, &pobj);
    if (NT_SUCCESS(st)) {
        name = PsGetProcessImageFileName(pobj);
        ObDereferenceObject(pobj);
    }
    return name;
}
