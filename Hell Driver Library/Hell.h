#ifndef __HELL_HEADER__
#define __HELL_HEADER__

#define HELL_DRIVER
#include <intrin.h>
#include <stdio.h>
#include "Common.h"

#pragma warning(disable:4201)

NTSTATUS CreateDevice(PDRIVER_OBJECT pDriver);
void DeleteDevice(PDRIVER_OBJECT pDriver);

void UnloadDriver(PDRIVER_OBJECT pDriver);
NTSTATUS IRPHandle(PDEVICE_OBJECT pDevice, PIRP pirp);
NTSTATUS IRPIoControl(PDEVICE_OBJECT pDevice, PIRP pirp);

#pragma region 宏/常量
#define null                             NULL
#define HELL_PARAMS(name)                (name)
#define HELL_DEBUG()                     __debugbreak()          
#define HLog(format, ...)                DbgPrint("R0 Hell: "##format"\n", ##__VA_ARGS__)
#define HELL_IN_LOCK(lock)               KIRQL hell_lock_irql;KeAcquireSpinLock(lock, &hell_lock_irql)
#define HELL_UN_LOCK(lock)               KeReleaseSpinLock(lock, hell_lock_irql)

#define PROCESS_TERMINATE                   (0x0001)
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

#pragma endregion

#pragma region 结构体


typedef struct _CALL_BACK_INFO {
	ULONG64 Unknown;
	ULONG64 Unknown2;
	UNICODE_STRING AltitudeString;
	LIST_ENTRY NextEntryItemList;
	ULONG64 Operations;
	PVOID ObHandle;
	PVOID ObjectType;
	ULONG64 PreCallBackAddr;
	ULONG64 PostCallBackAddr;
} CALL_BACK_INFO, * PCALL_BACK_INFO;


typedef struct _OB_CALLBACK {
	LIST_ENTRY          ListEntry;
	ULONG64             Unknown;
	PCALL_BACK_INFO     ObHandle;
	ULONG64             ObjTypeAddr;
	ULONG64             PreCall;
	ULONG64             PostCall;
} OB_CALLBACK, * POB_CALLBACK;

typedef struct _LDR_DATA_TABLE_ENTRY {
	LIST_ENTRY InLoadOrderLinks;
	LIST_ENTRY InMemoryOrderLinks;
	LIST_ENTRY InInitializationOrderLinks;
	PVOID DllBase;
	PVOID EntryPoint;
	ULONG SizeOfImage;
	UNICODE_STRING FullDllName;
	UNICODE_STRING BaseDllName;
	ULONG Flags;
	USHORT LoadCount;
	USHORT TlsIndex;
	union {
		LIST_ENTRY HashLinks;
		struct {
			PVOID SectionPointer;
			ULONG CheckSum;
		};
	};
	union {
		struct {
			ULONG TimeDateStamp;
		};
		struct {
			PVOID LoadedImports;
		};
	};
	struct _ACTIVATION_CONTEXT* EntryPointActivationContext;
	PVOID PatchInformation;
} LDR_DATA_TABLE_ENTRY, * PLDR_DATA_TABLE_ENTRY;






#pragma endregion

#pragma region 未导出函数定义

PUCHAR PsGetProcessImageFileName(__in PEPROCESS Process);

#pragma endregion

#endif // !__HELL_HEADER__