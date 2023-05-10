#include "Hell.h"
#include "SSDT.h"

NTSTATUS DriverEntry(_In_ PDRIVER_OBJECT pDriver, _In_ PUNICODE_STRING path) {
    HLog("��������<%wZ>", path);

    //HLog("DISPATCHER_HEADER Sizeof: 0x%llx", sizeof(DISPATCHER_HEADER));
    //HLog("KAFFINITY_EX Sizeof: 0x%llx", sizeof(KAFFINITY_EX));
    //HLog("KPROCESS64 Sizeof: 0x%llx", sizeof(KPROCESS));
    //HLog("EPROCESS Sizeof: 0x%llx", sizeof(EPROCESS));
    //HLog("PEB Sizeof: 0x%llx", sizeof(PEB));
    //HLog("HANDLE_TABLE Sizeof: 0x%llx", sizeof(HANDLE_TABLE));

    //HLog("MMWSL_INSTANCE Sizeof: 0x%llx", sizeof(MMWSL_INSTANCE));
    //HLog("MMSUPPORT_INSTANCE Sizeof: 0x%llx", sizeof(MMSUPPORT_INSTANCE));
    //HLog("MMSUPPORT_SHARED Sizeof: 0x%llx", sizeof(MMSUPPORT_SHARED));
    //HLog("MMSUPPORT_FULL Sizeof: 0x%llx", sizeof(MMSUPPORT_FULL));

    HELL_PARAMS(pDriver);
    HELL_PARAMS(path);
    pDriver->DriverUnload = UnloadDriver;

    PLDR_DATA pld;
    pld = (PLDR_DATA)pDriver->DriverSection;
    pld->Flags |= 0x20;

    NTSTATUS status = CreateDevice(pDriver);
    if (status == STATUS_SUCCESS) {
        HLog("�������سɹ�, װ��IRP");
        pDriver->MajorFunction[IRP_MJ_CREATE] = IRPHandle;
        pDriver->MajorFunction[IRP_MJ_CLOSE] = IRPHandle;
        pDriver->MajorFunction[IRP_MJ_DEVICE_CONTROL] = IRPIoControl;


        EnumRegisterHookCallBacks();
    }
    return status;
}

void UnloadDriver(PDRIVER_OBJECT pDriver) {
    HLog("ж�ؿ�ʼ");

    ProcessAccessHookUninstall();
    
    DeleteDevice(pDriver);

    HLog("ж�����");
}