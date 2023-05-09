#ifndef __HELL_STRUCT_HEADER__
#define __HELL_STRUCT_HEADER__

#include "Hell.h"
#include <NTSecAPI.h>


#define GDI_HANDLE_BUFFER_SIZE32	34
#define GDI_HANDLE_BUFFER_SIZE64	60
#ifndef _WIN64
#define GDI_HANDLE_BUFFER_SIZE GDI_HANDLE_BUFFER_SIZE32
#else
#define GDI_HANDLE_BUFFER_SIZE GDI_HANDLE_BUFFER_SIZE64
#endif

typedef ULONG GDI_HANDLE_BUFFER32[GDI_HANDLE_BUFFER_SIZE32];
typedef ULONG GDI_HANDLE_BUFFER64[GDI_HANDLE_BUFFER_SIZE64];
typedef ULONG GDI_HANDLE_BUFFER[GDI_HANDLE_BUFFER_SIZE];
typedef LONG KPRIORITY, * PKPRIORITY;


#pragma region NTSTATUS

#define STATUS_SUCCESS                   ((NTSTATUS)0x00000000L)
#define STATUS_INVALID_INFO_CLASS        ((NTSTATUS)0xC0000003L)
#define STATUS_NO_SUCH_USER              ((NTSTATUS)0xC0000064L)
#define STATUS_WRONG_PASSWORD            ((NTSTATUS)0xC000006AL)
#define STATUS_PASSWORD_RESTRICTION      ((NTSTATUS)0xC000006CL)
#define STATUS_LOGON_FAILURE             ((NTSTATUS)0xC000006DL)
#define STATUS_ACCOUNT_RESTRICTION       ((NTSTATUS)0xC000006EL)
#define STATUS_INVALID_LOGON_HOURS       ((NTSTATUS)0xC000006FL)
#define STATUS_INVALID_WORKSTATION       ((NTSTATUS)0xC0000070L)
#define STATUS_PASSWORD_EXPIRED          ((NTSTATUS)0xC0000071L)
#define STATUS_ACCOUNT_DISABLED          ((NTSTATUS)0xC0000072L)
#define STATUS_INSUFFICIENT_RESOURCES    ((NTSTATUS)0xC000009AL)
#define STATUS_ACCOUNT_EXPIRED           ((NTSTATUS)0xC0000193L)
#define STATUS_PASSWORD_MUST_CHANGE      ((NTSTATUS)0xC0000224L)
#define STATUS_ACCOUNT_LOCKED_OUT        ((NTSTATUS)0xC0000234L)
#define STATUS_UNSUCCESSFUL              ((NTSTATUS)0xC0000001L)
#define STATUS_DATA_ERROR                ((NTSTATUS)0xC000003EL)
#define STATUS_ABANDONED                 ((NTSTATUS)0x00000080L)
#define STATUS_OBJECT_NO_LONGER_EXISTS   ((NTSTATUS)0xC0190021L)

#define STATUS_NAME_TOO_LONG             ((NTSTATUS)0xC0000106L)
#define STATUS_LOG_FULL                  ((NTSTATUS)0xC01A001DL)
#define STATUS_FILE_CLOSED               ((NTSTATUS)0xC0000128L)

#define STATUS_QUOTA_EXCEEDED             ((NTSTATUS)0xC0000044L)
#define STATUS_FILE_IS_A_DIRECTORY        ((NTSTATUS)0xC00000BAL)
#define STATUS_REPARSE_POINT_NOT_RESOLVED ((NTSTATUS)0xC0000280L)
#define STATUS_NO_SUCH_FILE              ((NTSTATUS)0xC000000FL)
#define STATUS_PIPE_NOT_AVAILABLE        ((NTSTATUS)0xC00000ACL)
#define STATUS_INSTANCE_NOT_AVAILABLE    ((NTSTATUS)0xC00000ABL)
#define STATUS_INVALID_PIPE_STATE        ((NTSTATUS)0xC00000ADL)
#define STATUS_PIPE_BUSY                 ((NTSTATUS)0xC00000AEL)
#define STATUS_ILLEGAL_FUNCTION          ((NTSTATUS)0xC00000AFL)
#define STATUS_PIPE_DISCONNECTED         ((NTSTATUS)0xC00000B0L)
#define STATUS_PIPE_CLOSING              ((NTSTATUS)0xC00000B1L)
#define STATUS_PIPE_CONNECTED            ((NTSTATUS)0xC00000B2L)
#define STATUS_PIPE_LISTENING            ((NTSTATUS)0xC00000B3L)
#define STATUS_INVALID_READ_MODE         ((NTSTATUS)0xC00000B4L)
#define STATUS_PIPE_BROKEN               ((NTSTATUS)0xC000014BL)
#define STATUS_PIPE_EMPTY                ((NTSTATUS)0xC00000D9L)
#define STATUS_ENCOUNTERED_WRITE_IN_PROGRESS    ((NTSTATUS)0xC0000433)
#define STATUS_RESOURCE_IN_USE           ((NTSTATUS)0xC0000708L)
#define STATUS_OPEN_FAILED               ((NTSTATUS)0xC0000136L)
#define STATUS_UNEXPECTED_IO_ERROR       ((NTSTATUS)0xC00000E9L)
#define STATUS_NO_MORE_FILES             ((NTSTATUS)0x80000006L)
#define STATUS_DISK_FULL                 ((NTSTATUS)0xC000007FL)
#define STATUS_NOT_FOUND                 ((NTSTATUS)0xC0000225L)
#define STATUS_OBJECT_NAME_EXISTS        ((NTSTATUS)0x40000000L)
#define STATUS_OBJECT_NAME_COLLISION     ((NTSTATUS)0xC0000035L)
#define STATUS_NO_MORE_ENTRIES           ((NTSTATUS)0x8000001AL)
#define STATUS_END_OF_MEDIA              ((NTSTATUS)0x8000001EL)
#define STATUS_BEGINNING_OF_MEDIA        ((NTSTATUS)0x8000001FL)
#define STATUS_BUFFER_OVERFLOW           ((NTSTATUS)0x80000005L)
#define STATUS_INVALID_LOCK_SEQUENCE     ((NTSTATUS)0xC000001EL)
#define STATUS_FILE_FORCED_CLOSED        ((NTSTATUS)0xC00000B6L)
#define STATUS_INSUFF_SERVER_RESOURCES   ((NTSTATUS)0xC0000205L)
#define STATUS_NOT_IMPLEMENTED           ((NTSTATUS)0xC0000002L)
#define STATUS_CANCELLED                 ((NTSTATUS)0xC0000120L)
#define STATUS_ACCESS_DENIED             ((NTSTATUS)0xC0000022L)
#define STATUS_OBJECT_PATH_SYNTAX_BAD    ((NTSTATUS)0xC000003BL)
#define STATUS_INTERNAL_ERROR            ((NTSTATUS)0xC00000E5L)
#define STATUS_SHUTDOWN_IN_PROGRESS      ((NTSTATUS)0xC00002FEL)
#define STATUS_OBJECT_NAME_NOT_FOUND     ((NTSTATUS)0xC0000034L)
#define STATUS_OBJECT_TYPE_MISMATCH      ((NTSTATUS)0xC0000024L)
#define STATUS_NOT_SUPPORTED             ((NTSTATUS)0xC00000BBL)
#define STATUS_INFO_LENGTH_MISMATCH      ((NTSTATUS)0xC0000004L)
#define STATUS_BUFFER_TOO_SMALL          ((NTSTATUS)0xC0000023L)
#define STATUS_DISK_FULL                 ((NTSTATUS)0xC000007FL)
#define STATUS_OPEN_FAILED               ((NTSTATUS)0xC0000136L)
#define STATUS_DELETE_PENDING            ((NTSTATUS)0xC0000056L)
#define STATUS_SHARING_VIOLATION         ((NTSTATUS)0xC0000043L)
#define STATUS_NOT_IMPLEMENTED           ((NTSTATUS)0xC0000002L)
#define STATUS_DATA_ERROR                ((NTSTATUS)0xC000003EL)
#define STATUS_CRC_ERROR                 ((NTSTATUS)0xC000003FL)
#define STATUS_CANCELLED                 ((NTSTATUS)0xC0000120L)
#define STATUS_OBJECT_NAME_INVALID       ((NTSTATUS)0xC0000033L)
#define STATUS_BUFFER_TOO_SMALL          ((NTSTATUS)0xC0000023L)
#define STATUS_LOG_FULL                  ((NTSTATUS)0xC01A001DL)
#define STATUS_BUFFER_OVERFLOW           ((NTSTATUS)0x80000005L)
#define STATUS_DEVICE_CONFIGURATION_ERROR ((NTSTATUS)0xC0000182L)
#define STATUS_OBJECT_NO_LONGER_EXISTS   ((NTSTATUS)0xC0190021L)
#define STATUS_IO_TIMEOUT                ((NTSTATUS)0xC00000B5L)
#define STATUS_INVALID_BUFFER_SIZE       ((NTSTATUS)0xC0000206L)
#define STATUS_OBJECT_PATH_INVALID       ((NTSTATUS)0xC0000039L)
#define STATUS_NAME_TOO_LONG             ((NTSTATUS)0xC0000106L)
#define STATUS_REQUEST_OUT_OF_SEQUENCE   ((NTSTATUS)0xC000042AL)
#define STATUS_ALERTED                   ((NTSTATUS)0x00000101L)
#define STATUS_INVALID_DEVICE_REQUEST    ((NTSTATUS)0xC0000010L)
#define STATUS_FILE_CLOSED               ((NTSTATUS)0xC0000128L)
#define STATUS_RESOURCE_NOT_OWNED        ((NTSTATUS)0xC0000264L)
#define STATUS_NONEXISTENT_SECTOR        ((NTSTATUS)0xC0000015L)
#define STATUS_OBJECT_PATH_NOT_FOUND     ((NTSTATUS)0xC000003AL)
#define STATUS_INVALID_PARAMETER_MIX     ((NTSTATUS)0xC0000030L)
#define STATUS_END_OF_FILE               ((NTSTATUS)0xC0000011L)
#define STATUS_MORE_ENTRIES              ((NTSTATUS)0x00000105L)
#define STATUS_UNRECOGNIZED_VOLUME       ((NTSTATUS)0xC000014FL)
#define STATUS_NOT_A_DIRECTORY           ((NTSTATUS)0xC0000103L)
#define STATUS_SOURCE_ELEMENT_EMPTY      ((NTSTATUS)0xC0000283L)
#define STATUS_PRIVILEGE_NOT_HELD        ((NTSTATUS)0xC0000061L)
#define STATUS_NO_SUCH_DEVICE            ((NTSTATUS)0xC000000EL)
#define STATUS_FILE_TOO_LARGE            ((NTSTATUS)0xC0000904L)
#define STATUS_FILE_INVALID              ((NTSTATUS)0xC0000098L)
#define STATUS_NO_DATA_DETECTED          ((NTSTATUS)0x80000022L)
#define STATUS_RANGE_NOT_FOUND           ((NTSTATUS)0xC000028CL)
#define STATUS_REVISION_MISMATCH         ((NTSTATUS)0xC0000059L)
#define STATUS_ABANDONED_WAIT_63         ((NTSTATUS)0x000000BFL)
#define STATUS_WAIT_63                   ((NTSTATUS)0x0000003FL)
#define STATUS_WORKING_SET_QUOTA         ((NTSTATUS)0xC00000A1L)
#define STATUS_IO_DEVICE_ERROR           ((NTSTATUS)0xC0000185L)
#define STATUS_DIRECTORY_NOT_EMPTY       ((NTSTATUS)0xC0000101L)
#define STATUS_ABIOS_INVALID_COMMAND     ((NTSTATUS)0xC0000113L)
#define STATUS_INTERNAL_DB_ERROR         ((NTSTATUS)0xC0000158L)
#define STATUS_OBJECT_PATH_SYNTAX_BAD    ((NTSTATUS)0xC000003BL)
#define STATUS_INTERNAL_ERROR            ((NTSTATUS)0xC00000E5L)
#define STATUS_SHUTDOWN_IN_PROGRESS      ((NTSTATUS)0xC00002FEL)
#define STATUS_OBJECT_NAME_NOT_FOUND     ((NTSTATUS)0xC0000034L)
#define STATUS_OBJECT_TYPE_MISMATCH      ((NTSTATUS)0xC0000024L)
#define STATUS_NOT_SUPPORTED             ((NTSTATUS)0xC00000BBL)
#define STATUS_INFO_LENGTH_MISMATCH      ((NTSTATUS)0xC0000004L)
#define STATUS_INVALID_STATE_TRANSITION  ((NTSTATUS)0xC000A003L)
#define STATUS_INSUFFICIENT_POWER        ((NTSTATUS)0xC00002DEL)
#define STATUS_INTERNAL_DB_CORRUPTION    ((NTSTATUS)0xC00000E4L)
#define STATUS_MEMORY_NOT_ALLOCATED      ((NTSTATUS)0xC00000A0L)
#define STATUS_INVALID_PARAMETER_1       ((NTSTATUS)0xC00000EFL)
#define STATUS_INVALID_PARAMETER_2       ((NTSTATUS)0xC00000F0L)
#define STATUS_INVALID_PARAMETER_3       ((NTSTATUS)0xC00000F1L)
#define STATUS_INVALID_PARAMETER_4       ((NTSTATUS)0xC00000F2L)
#define STATUS_INVALID_PARAMETER_5       ((NTSTATUS)0xC00000F3L)
#define STATUS_INVALID_PARAMETER_6       ((NTSTATUS)0xC00000F4L)
#define STATUS_INVALID_PARAMETER_7       ((NTSTATUS)0xC00000F5L)
#define STATUS_INVALID_PARAMETER_8       ((NTSTATUS)0xC00000F6L)
#define STATUS_INVALID_PARAMETER_9       ((NTSTATUS)0xC00000F7L)
#define STATUS_INVALID_PARAMETER_10      ((NTSTATUS)0xC00000F8L)
#define STATUS_INVALID_PARAMETER_11      ((NTSTATUS)0xC00000F9L)
#define STATUS_INVALID_PARAMETER_12      ((NTSTATUS)0xC00000FAL)
#define STATUS_DISK_CORRUPT_ERROR        ((NTSTATUS)0xC0000032L)
#pragma endregion


#define RTL_MAX_DRIVE_LETTERS       32

#define RTL_CREATE_ENVIRONMENT_TRANSLATE			0x1 // Translate from multi-byte to Unicode
#define RTL_CREATE_ENVIRONMENT_TRANSLATE_FROM_OEM	0x2 // Translate from OEM to Unicode (Translate flag must also be set)
#define RTL_CREATE_ENVIRONMENT_EMPTY				0x4 // Create empty environment block

#define RTL_USER_PROCESS_PARAMETERS_NORMALIZED				0x01
#define RTL_USER_PROCESS_PARAMETERS_PROFILE_USER			0x02
#define RTL_USER_PROCESS_PARAMETERS_PROFILE_KERNEL			0x04
#define RTL_USER_PROCESS_PARAMETERS_PROFILE_SERVER			0x08
#define RTL_USER_PROCESS_PARAMETERS_RESERVE_1MB				0x20
#define RTL_USER_PROCESS_PARAMETERS_RESERVE_16MB			0x40
#define RTL_USER_PROCESS_PARAMETERS_CASE_SENSITIVE			0x80
#define RTL_USER_PROCESS_PARAMETERS_DISABLE_HEAP_DECOMMIT	0x100
#define RTL_USER_PROCESS_PARAMETERS_DLL_REDIRECTION_LOCAL	0x1000
#define RTL_USER_PROCESS_PARAMETERS_APP_MANIFEST_PRESENT	0x2000
#define RTL_USER_PROCESS_PARAMETERS_IMAGE_KEY_MISSING	 	0x4000
#define RTL_USER_PROCESS_PARAMETERS_NX_OPTIN				0x20000



#define NT_SUCCESS(Status)			((NTSTATUS)(Status) >= 0)
#define NT_ERROR(Status)			((((ULONG)(Status)) >> 30) == 3)



typedef struct _SYSTEM_PROCESS_INFORMATION {
    DWORD             dwNextEntryOffset;
    DWORD             dwNumberOfThreads;
    LARGE_INTEGER     qSpareLi1;
    LARGE_INTEGER     qSpareLi2;
    LARGE_INTEGER     qSpareLi3;
    LARGE_INTEGER     qCreateTime;
    LARGE_INTEGER     qUserTime;
    LARGE_INTEGER     qKernelTime;
    UNICODE_STRING    ImageName;
    INT               nBasePriority;
    DWORD             dwProcessId;
    DWORD             dwInheritedFromUniqueProcessId;
    DWORD             dwHandleCount;
    DWORD             dwSessionId;
    ULONG             dwSpareUl3;
    SIZE_T            tPeakVirtualSize;
    SIZE_T            tVirtualSize;
    DWORD             dwPageFaultCount;
    DWORD             dwPeakWorkingSetSize;
    DWORD             dwWorkingSetSize;
    SIZE_T            tQuotaPeakPagedPoolUsage;
    SIZE_T            tQuotaPagedPoolUsage;
    SIZE_T            tQuotaPeakNonPagedPoolUsage;
    SIZE_T            tQuotaNonPagedPoolUsage;
    SIZE_T            tPagefileUsage;
    SIZE_T            tPeakPagefileUsage;
    SIZE_T            tPrivatePageCount;
    LARGE_INTEGER     qReadOperationCount;
    LARGE_INTEGER     qWriteOperationCount;
    LARGE_INTEGER     qOtherOperationCount;
    LARGE_INTEGER     qReadTransferCount;
    LARGE_INTEGER     qWriteTransferCount;
    LARGE_INTEGER     qOtherTransferCount;
}SYSTEM_PROCESS_INFORMATION;

typedef struct _CURDIR {
	UNICODE_STRING DosPath;
	HANDLE Handle;
} CURDIR, * PCURDIR;

typedef struct _CLIENT_ID {
	HANDLE UniqueProcess;
	HANDLE UniqueThread;
} CLIENT_ID, * PCLIENT_ID;

typedef struct _SECTION_IMAGE_INFORMATION {
	PVOID TransferAddress; // Entry point
	ULONG ZeroBits;
	SIZE_T MaximumStackSize;
	SIZE_T CommittedStackSize;
	ULONG SubSystemType;
	union {
		struct {
			USHORT SubSystemMinorVersion;
			USHORT SubSystemMajorVersion;
		} s1;
		ULONG SubSystemVersion;
	} u1;
	union {
		struct {
			USHORT MajorOperatingSystemVersion;
			USHORT MinorOperatingSystemVersion;
		} s2;
		ULONG OperatingSystemVersion;
	} u2;
	USHORT ImageCharacteristics;
	USHORT DllCharacteristics;
	USHORT Machine;
	BOOLEAN ImageContainsCode;
	union {
		UCHAR ImageFlags;
		struct {
			UCHAR ComPlusNativeReady : 1;
			UCHAR ComPlusILOnly : 1;
			UCHAR ImageDynamicallyRelocated : 1;
			UCHAR ImageMappedFlat : 1;
			UCHAR BaseBelow4gb : 1;
			UCHAR ComPlusPrefer32bit : 1;
			UCHAR Reserved : 2;
		} s3;
	} u3;
	ULONG LoaderFlags;
	ULONG ImageFileSize;
	ULONG CheckSum;
} SECTION_IMAGE_INFORMATION, * PSECTION_IMAGE_INFORMATION;

typedef struct _RTL_USER_PROCESS_INFORMATION {
	ULONG Length;
	HANDLE ProcessHandle;
	HANDLE ThreadHandle;
	CLIENT_ID ClientId;
	SECTION_IMAGE_INFORMATION ImageInformation;
} RTL_USER_PROCESS_INFORMATION, * PRTL_USER_PROCESS_INFORMATION;

typedef struct _RTL_DRIVE_LETTER_CURDIR {
	USHORT Flags;
	USHORT Length;
	ULONG TimeStamp;
	UNICODE_STRING DosPath;
} RTL_DRIVE_LETTER_CURDIR, * PRTL_DRIVE_LETTER_CURDIR;

typedef struct _RTL_BUFFER {
	PUCHAR Buffer;
	PUCHAR StaticBuffer;
	SIZE_T Size;
	SIZE_T StaticSize;
	SIZE_T ReservedForAllocatedSize; // for future doubling
	PVOID ReservedForIMalloc; // for future pluggable growth
} RTL_BUFFER, * PRTL_BUFFER;

typedef struct _RTL_UNICODE_STRING_BUFFER {
	UNICODE_STRING String;
	RTL_BUFFER ByteBuffer;
	UCHAR MinimumStaticBufferForTerminalNul[sizeof(WCHAR)];
} RTL_UNICODE_STRING_BUFFER, * PRTL_UNICODE_STRING_BUFFER;

typedef struct _RTL_USER_PROCESS_PARAMETERS {
	ULONG MaximumLength;
	ULONG Length;

	ULONG Flags;
	ULONG DebugFlags;

	HANDLE ConsoleHandle;
	ULONG ConsoleFlags;
	HANDLE StandardInput;
	HANDLE StandardOutput;
	HANDLE StandardError;

	CURDIR CurrentDirectory;
	UNICODE_STRING DllPath;
	UNICODE_STRING ImagePathName;
	UNICODE_STRING CommandLine;
	PWCHAR Environment;

	ULONG StartingX;
	ULONG StartingY;
	ULONG CountX;
	ULONG CountY;
	ULONG CountCharsX;
	ULONG CountCharsY;
	ULONG FillAttribute;

	ULONG WindowFlags;
	ULONG ShowWindowFlags;
	UNICODE_STRING WindowTitle;
	UNICODE_STRING DesktopInfo;
	UNICODE_STRING ShellInfo;
	UNICODE_STRING RuntimeData;
	RTL_DRIVE_LETTER_CURDIR CurrentDirectories[RTL_MAX_DRIVE_LETTERS];

	ULONG_PTR EnvironmentSize;
	ULONG_PTR EnvironmentVersion;
	PVOID PackageDependencyData;
	ULONG ProcessGroupId;
	ULONG LoaderThreads;
} RTL_USER_PROCESS_PARAMETERS, * PRTL_USER_PROCESS_PARAMETERS;

typedef struct _PEB_LDR_DATA {
	ULONG Length;
	BOOLEAN Initialized;
	HANDLE SsHandle;
	LIST_ENTRY InLoadOrderModuleList;
	LIST_ENTRY InMemoryOrderModuleList;
	LIST_ENTRY InInitializationOrderModuleList;
	PVOID EntryInProgress;
	BOOLEAN ShutdownInProgress;
	HANDLE ShutdownThreadId;
} PEB_LDR_DATA, * PPEB_LDR_DATA;

typedef struct _PEB {
	BOOLEAN InheritedAddressSpace;
	BOOLEAN ReadImageFileExecOptions;
	BOOLEAN BeingDebugged;
	union {
		BOOLEAN BitField;
		struct {
			BOOLEAN ImageUsesLargePages : 1;
			BOOLEAN IsProtectedProcess : 1;
			BOOLEAN IsImageDynamicallyRelocated : 1;
			BOOLEAN SkipPatchingUser32Forwarders : 1;
			BOOLEAN IsPackagedProcess : 1;
			BOOLEAN IsAppContainer : 1;
			BOOLEAN IsProtectedProcessLight : 1;
			BOOLEAN IsLongPathAwareProcess : 1;
		} s1;
	} u1;

	HANDLE Mutant;

	PVOID ImageBaseAddress;
	PPEB_LDR_DATA Ldr;
	PRTL_USER_PROCESS_PARAMETERS ProcessParameters;
	PVOID SubSystemData;
	PVOID ProcessHeap;
	PRTL_CRITICAL_SECTION FastPebLock;
	PVOID AtlThunkSListPtr;
	PVOID IFEOKey;
	union {
		ULONG CrossProcessFlags;
		struct {
			ULONG ProcessInJob : 1;
			ULONG ProcessInitializing : 1;
			ULONG ProcessUsingVEH : 1;
			ULONG ProcessUsingVCH : 1;
			ULONG ProcessUsingFTH : 1;
			ULONG ProcessPreviouslyThrottled : 1;
			ULONG ProcessCurrentlyThrottled : 1;
			ULONG ReservedBits0 : 25;
		} s2;
	} u2;
	union {
		PVOID KernelCallbackTable;
		PVOID UserSharedInfoPtr;
	} u3;
	ULONG SystemReserved[1];
	ULONG AtlThunkSListPtr32;
	PVOID ApiSetMap;
	ULONG TlsExpansionCounter;
	PVOID TlsBitmap;
	ULONG TlsBitmapBits[2];

	PVOID ReadOnlySharedMemoryBase;
	PVOID SharedData; // HotpatchInformation
	PVOID* ReadOnlyStaticServerData;

	PVOID AnsiCodePageData; // PCPTABLEINFO
	PVOID OemCodePageData; // PCPTABLEINFO
	PVOID UnicodeCaseTableData; // PNLSTABLEINFO

	ULONG NumberOfProcessors;
	ULONG NtGlobalFlag;

	LARGE_INTEGER CriticalSectionTimeout;
	SIZE_T HeapSegmentReserve;
	SIZE_T HeapSegmentCommit;
	SIZE_T HeapDeCommitTotalFreeThreshold;
	SIZE_T HeapDeCommitFreeBlockThreshold;

	ULONG NumberOfHeaps;
	ULONG MaximumNumberOfHeaps;
	PVOID* ProcessHeaps; // PHEAP

	PVOID GdiSharedHandleTable;
	PVOID ProcessStarterHelper;
	ULONG GdiDCAttributeList;

	PRTL_CRITICAL_SECTION LoaderLock;

	ULONG OSMajorVersion;
	ULONG OSMinorVersion;
	USHORT OSBuildNumber;
	USHORT OSCSDVersion;
	ULONG OSPlatformId;
	ULONG ImageSubsystem;
	ULONG ImageSubsystemMajorVersion;
	ULONG ImageSubsystemMinorVersion;
	ULONG_PTR ActiveProcessAffinityMask;
	GDI_HANDLE_BUFFER GdiHandleBuffer;
	PVOID PostProcessInitRoutine;

	PVOID TlsExpansionBitmap;
	ULONG TlsExpansionBitmapBits[32];

	ULONG SessionId;

	ULARGE_INTEGER AppCompatFlags;
	ULARGE_INTEGER AppCompatFlagsUser;
	PVOID pShimData;
	PVOID AppCompatInfo; // APPCOMPAT_EXE_DATA

	UNICODE_STRING CSDVersion;

	PVOID ActivationContextData; // ACTIVATION_CONTEXT_DATA
	PVOID ProcessAssemblyStorageMap; // ASSEMBLY_STORAGE_MAP
	PVOID SystemDefaultActivationContextData; // ACTIVATION_CONTEXT_DATA
	PVOID SystemAssemblyStorageMap; // ASSEMBLY_STORAGE_MAP

	SIZE_T MinimumStackCommit;

	PVOID* FlsCallback;
	LIST_ENTRY FlsListHead;
	PVOID FlsBitmap;
	ULONG FlsBitmapBits[FLS_MAXIMUM_AVAILABLE / (sizeof(ULONG) * 8)];
	ULONG FlsHighIndex;

	PVOID WerRegistrationData;
	PVOID WerShipAssertPtr;
	PVOID pUnused; // pContextData
	PVOID pImageHeaderHash;
	union {
		ULONG TracingFlags;
		struct {
			ULONG HeapTracingEnabled : 1;
			ULONG CritSecTracingEnabled : 1;
			ULONG LibLoaderTracingEnabled : 1;
			ULONG SpareTracingBits : 29;
		} s3;
	} u4;
	ULONGLONG CsrServerReadOnlySharedMemoryBase;
	PVOID TppWorkerpListLock;
	LIST_ENTRY TppWorkerpList;
	PVOID WaitOnAddressHashTable[128];
	PVOID TelemetryCoverageHeader; // REDSTONE3
	ULONG CloudFileFlags;
} PEB, * PPEB;

typedef struct _PROCESS_BASIC_INFORMATION {
	NTSTATUS ExitStatus;
	PPEB PebBaseAddress;
	ULONG_PTR AffinityMask;
	KPRIORITY BasePriority;
	HANDLE UniqueProcessId;
	HANDLE InheritedFromUniqueProcessId;
} PROCESS_BASIC_INFORMATION, * PPROCESS_BASIC_INFORMATION;

typedef struct _SYSTEM_HANDLE_TABLE_ENTRY_INFO {
	USHORT ProcessId;
	USHORT CreateBackTraceIndex;
	UCHAR ObjectTypeNumber;
	UCHAR Flags;
	USHORT Handle;
	PVOID Object;
	ACCESS_MASK GrantedAccess;
} SYSTEM_HANDLE_TABLE_ENTRY_INFO, * PSYSTEM_HANDLE_TABLE_ENTRY_INFO;

typedef struct _SYSTEM_HANDLE_INFORMATION {
	ULONG NumberOfHandles;
	SYSTEM_HANDLE_TABLE_ENTRY_INFO Handles[1];
} SYSTEM_HANDLE_INFORMATION, * PSYSTEM_HANDLE_INFORMATION;

typedef struct _OBJECT_NAME_INFORMATION {
	UNICODE_STRING Name;
} OBJECT_NAME_INFORMATION, * POBJECT_NAME_INFORMATION;

typedef struct _IO_STATUS_BLOCK {
	union {
		NTSTATUS Status;
		PVOID Pointer;
	};
	PULONG Information;
} IO_STATUS_BLOCK, * PIO_STATUS_BLOCK;











#ifdef __cplusplus
typedef enum class _FILE_INFORMATION_CLASS {
#else
typedef enum _FILE_INFORMATION_CLASS {
#endif // __cplusplus
	FileDirectoryInformation = 1,
	FileFullDirectoryInformation,   // 2
	FileBothDirectoryInformation,   // 3
	FileBasicInformation,           // 4
	FileStandardInformation,        // 5
	FileInternalInformation,        // 6
	FileEaInformation,              // 7
	FileAccessInformation,          // 8
	FileNameInformation,            // 9
	FileRenameInformation,          // 10
	FileLinkInformation,            // 11
	FileNamesInformation,           // 12
	FileDispositionInformation,     // 13
	FilePositionInformation,        // 14
	FileFullEaInformation,          // 15
	FileModeInformation,            // 16
	FileAlignmentInformation,       // 17
	FileAllInformation,             // 18
	FileAllocationInformation,      // 19
	FileEndOfFileInformation,       // 20
	FileAlternateNameInformation,   // 21
	FileStreamInformation,          // 22
	FilePipeInformation,            // 23
	FilePipeLocalInformation,       // 24
	FilePipeRemoteInformation,      // 25
	FileMailslotQueryInformation,   // 26
	FileMailslotSetInformation,     // 27
	FileCompressionInformation,     // 28
	FileObjectIdInformation,        // 29
	FileCompletionInformation,      // 30
	FileMoveClusterInformation,     // 31
	FileQuotaInformation,           // 32
	FileReparsePointInformation,    // 33
	FileNetworkOpenInformation,     // 34
	FileAttributeTagInformation,    // 35
	FileTrackingInformation,        // 36
	FileIdBothDirectoryInformation, // 37
	FileIdFullDirectoryInformation, // 38
	FileValidDataLengthInformation, // 39
	FileShortNameInformation,       // 40
	FileIoCompletionNotificationInformation, // 41
	FileIoStatusBlockRangeInformation,       // 42
	FileIoPriorityHintInformation,           // 43
	FileSfioReserveInformation,              // 44
	FileSfioVolumeInformation,               // 45
	FileHardLinkInformation,                 // 46
	FileProcessIdsUsingFileInformation,      // 47
	FileNormalizedNameInformation,           // 48
	FileNetworkPhysicalNameInformation,      // 49
	FileIdGlobalTxDirectoryInformation,      // 50
	FileIsRemoteDeviceInformation,           // 51
	FileUnusedInformation,                   // 52
	FileNumaNodeInformation,                 // 53
	FileStandardLinkInformation,             // 54
	FileRemoteProtocolInformation,           // 55
	FileRenameInformationBypassAccessCheck,  // 56
	FileLinkInformationBypassAccessCheck,    // 57
	FileVolumeNameInformation,               // 58
	FileIdInformation,                       // 59
	FileIdExtdDirectoryInformation,          // 60
	FileReplaceCompletionInformation,        // 61
	FileHardLinkFullIdInformation,           // 62
	FileMaximumInformation
} FILE_INFORMATION_CLASS, * PFILE_INFORMATION_CLASS;


#ifdef __cplusplus
typedef enum class _SYSTEM_INFORMATION_CLASS {
#else
typedef enum _SYSTEM_INFORMATION_CLASS {
#endif // __cplusplus
	SystemBasicInformation,             // 0x002C
	SystemProcessorInformation,         // 0x000C
	SystemPerformanceInformation,       // 0x0138
	SystemTimeInformation,              // 0x0020
	SystemPathInformation,              // not implemented
	SystemProcessInformation,           // 0x00F8+ per process
	SystemCallInformation,              // 0x0018 + (n * 0x0004)
	SystemConfigurationInformation,     // 0x0018
	SystemProcessorCounters,            // 0x0030 per cpu
	SystemGlobalFlag,                   // 0x0004
	SystemInfo10,                       // not implemented
	SystemModuleInformation,            // 0x0004 + (n * 0x011C)
	SystemLockInformation,              // 0x0004 + (n * 0x0024)
	SystemInfo13,                       // not implemented
	SystemPagedPoolInformation,         // checked build only
	SystemNonPagedPoolInformation,      // checked build only
	SystemHandleInformation,            // 0x0004  + (n * 0x0010)
	SystemObjectInformation,            // 0x0038+ + (n * 0x0030+)
	SystemPagefileInformation,          // 0x0018+ per page file
	SystemInstemulInformation,          // 0x0088
	SystemInfo20,                       // invalid info class
	SystemCacheInformation,             // 0x0024
	SystemPoolTagInformation,           // 0x0004 + (n * 0x001C)
	SystemProcessorStatistics,          // 0x0000, or 0x0018 per cpu
	SystemDpcInformation,               // 0x0014
	SystemMemoryUsageInformation1,      // checked build only
	SystemLoadImage,                    // 0x0018, set mode only
	SystemUnloadImage,                  // 0x0004, set mode only
	SystemTimeAdjustmentInformation,    // 0x000C, 0x0008 writeable
	SystemMemoryUsageInformation2,      // checked build only
	SystemInfo30,                       // checked build only
	SystemInfo31,                       // checked build only
	SystemCrashDumpInformation,         // 0x0004
	SystemExceptionInformation,         // 0x0010
	SystemCrashDumpStateInformation,    // 0x0008
	SystemDebuggerInformation,          // 0x0002
	SystemThreadSwitchInformation,      // 0x0030
	SystemRegistryQuotaInformation,     // 0x000C
	SystemLoadDriver,                   // 0x0008, set mode only
	SystemPrioritySeparationInformation,// 0x0004, set mode only
	SystemInfo40,                       // not implemented
	SystemInfo41,                       // not implemented
	SystemInfo42,                       // invalid info class
	SystemInfo43,                       // invalid info class
	SystemTimeZoneInformation,          // 0x00AC
	SystemLookasideInformation,         // n * 0x0020
	SystemSetTimeSlipEvent,             // set mode only
	SystemCreateSession,                // WTS, set mode only
	SystemDeleteSession,                // WTS, set mode only
	SystemInfo49,                       // invalid info class
	SystemRangeStartInformation,        // 0x0004
	SystemVerifierInformation,          // 0x0068
	SystemAddVerifier,                  // set mode only
	SystemSessionProcessesInformation,  // WTS
}  SYSTEM_INFORMATION_CLASS, * PSYSTEM_INFORMATION_CLASS, ** PPSYSTEM_INFORMATION_CLASS;

#ifdef __cplusplus
typedef enum class _PROCESSINFOCLASS {
#else
typedef enum _PROCESSINFOCLASS {
#endif // __cplusplus
	ProcessBasicInformation, // q: PROCESS_BASIC_INFORMATION, PROCESS_EXTENDED_BASIC_INFORMATION
	ProcessQuotaLimits, // qs: QUOTA_LIMITS, QUOTA_LIMITS_EX
	ProcessIoCounters, // q: IO_COUNTERS
	ProcessVmCounters, // q: VM_COUNTERS, VM_COUNTERS_EX, VM_COUNTERS_EX2
	ProcessTimes, // q: KERNEL_USER_TIMES
	ProcessBasePriority, // s: KPRIORITY
	ProcessRaisePriority, // s: ULONG
	ProcessDebugPort, // q: HANDLE
	ProcessExceptionPort, // s: PROCESS_EXCEPTION_PORT (requires SeTcbPrivilege)
	ProcessAccessToken, // s: PROCESS_ACCESS_TOKEN
	ProcessLdtInformation, // qs: PROCESS_LDT_INFORMATION // 10
	ProcessLdtSize, // s: PROCESS_LDT_SIZE
	ProcessDefaultHardErrorMode, // qs: ULONG
	ProcessIoPortHandlers, // (kernel-mode only) // PROCESS_IO_PORT_HANDLER_INFORMATION
	ProcessPooledUsageAndLimits, // q: POOLED_USAGE_AND_LIMITS
	ProcessWorkingSetWatch, // q: PROCESS_WS_WATCH_INFORMATION[]; s: void
	ProcessUserModeIOPL, // qs: ULONG (requires SeTcbPrivilege)
	ProcessEnableAlignmentFaultFixup, // s: BOOLEAN
	ProcessPriorityClass, // qs: PROCESS_PRIORITY_CLASS
	ProcessWx86Information, // qs: ULONG (requires SeTcbPrivilege) (VdmAllowed)
	ProcessHandleCount, // q: ULONG, PROCESS_HANDLE_INFORMATION // 20
	ProcessAffinityMask, // (q >WIN7)s: KAFFINITY, qs: GROUP_AFFINITY
	ProcessPriorityBoost, // qs: ULONG
	ProcessDeviceMap, // qs: PROCESS_DEVICEMAP_INFORMATION, PROCESS_DEVICEMAP_INFORMATION_EX
	ProcessSessionInformation, // q: PROCESS_SESSION_INFORMATION
	ProcessForegroundInformation, // s: PROCESS_FOREGROUND_BACKGROUND
	ProcessWow64Information, // q: ULONG_PTR
	ProcessImageFileName, // q: UNICODE_STRING
	ProcessLUIDDeviceMapsEnabled, // q: ULONG
	ProcessBreakOnTermination, // qs: ULONG
	ProcessDebugObjectHandle, // q: HANDLE // 30
	ProcessDebugFlags, // qs: ULONG
	ProcessHandleTracing, // q: PROCESS_HANDLE_TRACING_QUERY; s: size 0 disables, otherwise enables
	ProcessIoPriority, // qs: IO_PRIORITY_HINT
	ProcessExecuteFlags, // qs: ULONG
	ProcessTlsInformation, // PROCESS_TLS_INFORMATION // ProcessResourceManagement
	ProcessCookie, // q: ULONG
	ProcessImageInformation, // q: SECTION_IMAGE_INFORMATION
	ProcessCycleTime, // q: PROCESS_CYCLE_TIME_INFORMATION // since VISTA
	ProcessPagePriority, // qs: PAGE_PRIORITY_INFORMATION
	ProcessInstrumentationCallback, // s: PVOID or PROCESS_INSTRUMENTATION_CALLBACK_INFORMATION // 40
	ProcessThreadStackAllocation, // s: PROCESS_STACK_ALLOCATION_INFORMATION, PROCESS_STACK_ALLOCATION_INFORMATION_EX
	ProcessWorkingSetWatchEx, // q: PROCESS_WS_WATCH_INFORMATION_EX[]
	ProcessImageFileNameWin32, // q: UNICODE_STRING
	ProcessImageFileMapping, // q: HANDLE (input)
	ProcessAffinityUpdateMode, // qs: PROCESS_AFFINITY_UPDATE_MODE
	ProcessMemoryAllocationMode, // qs: PROCESS_MEMORY_ALLOCATION_MODE
	ProcessGroupInformation, // q: USHORT[]
	ProcessTokenVirtualizationEnabled, // s: ULONG
	ProcessConsoleHostProcess, // q: ULONG_PTR // ProcessOwnerInformation
	ProcessWindowInformation, // q: PROCESS_WINDOW_INFORMATION // 50
	ProcessHandleInformation, // q: PROCESS_HANDLE_SNAPSHOT_INFORMATION // since WIN8
	ProcessMitigationPolicy, // s: PROCESS_MITIGATION_POLICY_INFORMATION
	ProcessDynamicFunctionTableInformation,
	ProcessHandleCheckingMode, // qs: ULONG; s: 0 disables, otherwise enables
	ProcessKeepAliveCount, // q: PROCESS_KEEPALIVE_COUNT_INFORMATION
	ProcessRevokeFileHandles, // s: PROCESS_REVOKE_FILE_HANDLES_INFORMATION
	ProcessWorkingSetControl, // s: PROCESS_WORKING_SET_CONTROL
	ProcessHandleTable, // q: ULONG[] // since WINBLUE
	ProcessCheckStackExtentsMode, // qs: ULONG // KPROCESS->CheckStackExtents (CFG)
	ProcessCommandLineInformation, // q: UNICODE_STRING // 60
	ProcessProtectionInformation, // q: PS_PROTECTION
	ProcessMemoryExhaustion, // PROCESS_MEMORY_EXHAUSTION_INFO // since THRESHOLD
	ProcessFaultInformation, // PROCESS_FAULT_INFORMATION
	ProcessTelemetryIdInformation, // q: PROCESS_TELEMETRY_ID_INFORMATION
	ProcessCommitReleaseInformation, // PROCESS_COMMIT_RELEASE_INFORMATION
	ProcessDefaultCpuSetsInformation, // SYSTEM_CPU_SET_INFORMATION[5]
	ProcessAllowedCpuSetsInformation, // SYSTEM_CPU_SET_INFORMATION[5]
	ProcessSubsystemProcess,
	ProcessJobMemoryInformation, // q: PROCESS_JOB_MEMORY_INFO
	ProcessInPrivate, // s: void // ETW // since THRESHOLD2 // 70
	ProcessRaiseUMExceptionOnInvalidHandleClose, // qs: ULONG; s: 0 disables, otherwise enables
	ProcessIumChallengeResponse,
	ProcessChildProcessInformation, // q: PROCESS_CHILD_PROCESS_INFORMATION
	ProcessHighGraphicsPriorityInformation, // qs: BOOLEAN (requires SeTcbPrivilege)
	ProcessSubsystemInformation, // q: SUBSYSTEM_INFORMATION_TYPE // since REDSTONE2
	ProcessEnergyValues, // q: PROCESS_ENERGY_VALUES, PROCESS_EXTENDED_ENERGY_VALUES
	ProcessPowerThrottlingState, // qs: POWER_THROTTLING_PROCESS_STATE
	ProcessReserved3Information, // ProcessActivityThrottlePolicy // PROCESS_ACTIVITY_THROTTLE_POLICY
	ProcessWin32kSyscallFilterInformation, // q: WIN32K_SYSCALL_FILTER
	ProcessDisableSystemAllowedCpuSets, // 80
	ProcessWakeInformation, // PROCESS_WAKE_INFORMATION
	ProcessEnergyTrackingState, // PROCESS_ENERGY_TRACKING_STATE
	ProcessManageWritesToExecutableMemory, // MANAGE_WRITES_TO_EXECUTABLE_MEMORY // since REDSTONE3
	ProcessCaptureTrustletLiveDump,
	ProcessTelemetryCoverage,
	ProcessEnclaveInformation,
	ProcessEnableReadWriteVmLogging, // PROCESS_READWRITEVM_LOGGING_INFORMATION
	ProcessUptimeInformation, // q: PROCESS_UPTIME_INFORMATION
	ProcessImageSection, // q: HANDLE
	ProcessDebugAuthInformation, // since REDSTONE4 // 90
	ProcessSystemResourceManagement, // PROCESS_SYSTEM_RESOURCE_MANAGEMENT
	ProcessSequenceNumber, // q: ULONGLONG
	ProcessLoaderDetour, // since REDSTONE5
	ProcessSecurityDomainInformation, // PROCESS_SECURITY_DOMAIN_INFORMATION
	ProcessCombineSecurityDomainsInformation, // PROCESS_COMBINE_SECURITY_DOMAINS_INFORMATION
	ProcessEnableLogging, // PROCESS_LOGGING_INFORMATION
	ProcessLeapSecondInformation, // PROCESS_LEAP_SECOND_INFORMATION
	ProcessFiberShadowStackAllocation, // PROCESS_FIBER_SHADOW_STACK_ALLOCATION_INFORMATION // since 19H1
	ProcessFreeFiberShadowStackAllocation, // PROCESS_FREE_FIBER_SHADOW_STACK_ALLOCATION_INFORMATION
	ProcessAltSystemCallInformation, // qs: BOOLEAN (kernel-mode only) // INT2E // since 20H1 // 100
	ProcessDynamicEHContinuationTargets, // PROCESS_DYNAMIC_EH_CONTINUATION_TARGETS_INFORMATION
	ProcessDynamicEnforcedCetCompatibleRanges, // PROCESS_DYNAMIC_ENFORCED_ADDRESS_RANGE_INFORMATION // since 20H2
	ProcessCreateStateChange, // since WIN11
	ProcessApplyStateChange,
	ProcessEnableOptionalXStateFeatures,
	ProcessAltPrefetchParam, // since 22H1
	ProcessAssignCpuPartitions,
	ProcessPriorityClassEx, // s: PROCESS_PRIORITY_CLASS_EX
	ProcessMembershipInformation,
	ProcessEffectiveIoPriority, // q: IO_PRIORITY_HINT
	ProcessEffectivePagePriority, // q: ULONG
	MaxProcessInfoClass
} PROCESSINFO_CLASS;


#ifdef __cplusplus
typedef enum class _OBJECT_INFORMATION_CLASS {
#else
typedef enum _OBJECT_INFORMATION_CLASS {
#endif // __cplusplus
	ObjectBasicInformation, // OBJECT_BASIC_INFORMATION
	ObjectNameInformation, // OBJECT_NAME_INFORMATION
	ObjectTypeInformation, // OBJECT_TYPE_INFORMATION
	ObjectTypesInformation, // OBJECT_TYPES_INFORMATION
	ObjectHandleFlagInformation, // OBJECT_HANDLE_FLAG_INFORMATION
	ObjectSessionInformation,
	ObjectSessionObjectInformation,
	MaxObjectInfoClass
} OBJECT_INFORMATION_CLASS;

#ifdef __cplusplus
typedef enum class _MEMORY_INFORMATION_CLASS {
#else
typedef enum _MEMORY_INFORMATION_CLASS {
#endif // __cplusplus
	MemoryBasicInformation, // MEMORY_BASIC_INFORMATION
	MemoryWorkingSetInformation, // MEMORY_WORKING_SET_INFORMATION
	MemoryMappedFilenameInformation, // UNICODE_STRING
	MemoryRegionInformation, // MEMORY_REGION_INFORMATION
	MemoryWorkingSetExInformation, // MEMORY_WORKING_SET_EX_INFORMATION
	MemorySharedCommitInformation, // MEMORY_SHARED_COMMIT_INFORMATION
	MemoryImageInformation, // MEMORY_IMAGE_INFORMATION
	MemoryRegionInformationEx,
	MemoryPrivilegedBasicInformation
} MEMORY_INFORMATION_CLASS;

#ifdef __cplusplus
typedef enum class _NT_PRODUCT_TYPE {
#else
typedef enum _NT_PRODUCT_TYPE {
#endif // __cplusplus
	NtProductWinNt = 1,
	NtProductLanManNt,
	NtProductServer
} NT_PRODUCT_TYPE, * PNT_PRODUCT_TYPE;

#endif // !__HELL_STRUCT_HEADER__