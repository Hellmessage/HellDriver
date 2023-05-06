#ifndef __HELL_HEADER__
#define __HELL_HEADER__

#define HELL_DRIVER
#include <intrin.h>
#include "Common.h"


//#pragma warning(disable:4996)


NTSTATUS CreateDevice(PDRIVER_OBJECT pDriver);
void DeleteDevice(PDRIVER_OBJECT pDriver);

void UnloadDriver(PDRIVER_OBJECT pDriver);
NTSTATUS IRPHandle(PDEVICE_OBJECT pDevice, PIRP pirp);
NTSTATUS IRPIoControl(PDEVICE_OBJECT pDevice, PIRP pirp);

#pragma region 宏/常量
#define null                             NULL
#define HELL_PARAMS(name)                (name)
#define HELL_DEBUG()                     __debugbreak()
#define HLog(format, ...)                DbgPrint("R0 Hell: "#format"\n", __VA_ARGS__)
#define HELL_IN_LOCK(lock)               KIRQL irql;KeAcquireSpinLock(lock, &irql)
#define HELL_UN_LOCK(lock)               KeReleaseSpinLock(&g_Lock, irql)



#define PROCESS_CREATE_THREAD               (0x0002)  
#define PROCESS_SET_SESSIONID               (0x0004)  
#define PROCESS_VM_OPERATION                (0x0008)  
#define PROCESS_VM_READ                     (0x0010)  
#define PROCESS_VM_WRITE                    (0x0020)  
#define PROCESS_DUP_HANDLE                  (0x0040)  
#define PROCESS_CREATE_PROCESS              (0x0080)  
#define PROCESS_SET_QUOTA                   (0x0100)  
#define PROCESS_SET_INFORMATION             (0x0200)  
#define PROCESS_QUERY_INFORMATION           (0x0400)  
#define PROCESS_SUSPEND_RESUME              (0x0800)  
#define PROCESS_QUERY_LIMITED_INFORMATION   (0x1000)  
#define PROCESS_SET_LIMITED_INFORMATION     (0x2000)

#define PROCESS_TERMINATE                   (0x0001)
#define PROCESS_TERMINATE_0                 (0x1001)
#define PROCESS_KILL_F                      (0x1401)
#define PROCESS_TERMINATE_KILL              (0x1041)

#pragma endregion







#pragma region 结构体

#ifdef _WIN64
typedef struct _LDR_DATA {
	LIST_ENTRY			listEntry;
	ULONG64				__Undefined1;
	ULONG64				__Undefined2;
	ULONG64				__Undefined3;
	ULONG64				NonPagedDebugInfo;
	ULONG64				DllBase;
	ULONG64				EntryPoint;
	ULONG				SizeOfImage;
	UNICODE_STRING		path;
	UNICODE_STRING		name;
	ULONG				Flags;
}LDR_DATA, * PLDR_DATA;
#else
typedef struct _LDR_DATA {
	LIST_ENTRY			listEntry;
	ULONG				unknown1;
	ULONG				unknown2;
	ULONG				unknown3;
	ULONG				unknown4;
	ULONG				unknown5;
	ULONG				unknown6;
	ULONG				unknown7;
	UNICODE_STRING		path;
	UNICODE_STRING		name;
	ULONG				Flags;
}LDR_DATA, * PLDR_DATA;
#endif

#pragma endregion

#pragma region 未导出函数定义

PUCHAR PsGetProcessImageFileName(__in PEPROCESS Process);

#pragma endregion

#endif // !__HELL_HEADER__