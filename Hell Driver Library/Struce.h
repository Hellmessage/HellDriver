#ifndef __HELL_DRIVER_STRUCT_HEADER__
#define __HELL_DRIVER_STRUCT_HEADER__

#include "Hell.h"

#define FLS_MAXIMUM_AVAILABLE 128
#define TLS_MINIMUM_AVAILABLE 64

#ifdef _WIN64
#define GDI_HANDLE_BUFFER_SIZE 60
#else
#define GDI_HANDLE_BUFFER_SIZE 34
#endif
typedef ULONG GDI_HANDLE_BUFFER[GDI_HANDLE_BUFFER_SIZE];

typedef struct _KSCHEDULING_GROUP* PKSCHEDULING_GROUP;
typedef struct _EJOB* PEJOB;
typedef struct _PAGEFAULT_HISTORY* PPAGEFAULT_HISTORY;
typedef struct _RTL_USER_PROCESS_PARAMETERS* PRTL_USER_PROCESS_PARAMETERS;
typedef struct _RTL_CRITICAL_SECTION* PRTL_CRITICAL_SECTION;
typedef struct _ACTIVATION_CONTEXT_DATA* PACTIVATION_CONTEXT_DATA;
typedef struct _ASSEMBLY_STORAGE_MAP* PASSEMBLY_STORAGE_MAP;
typedef struct _LEAP_SECOND_DATA* PLEAP_SECOND_DATA;
typedef struct _MM_SESSION_SPACE* PMM_SESSION_SPACE;
typedef struct _EPROCESS_QUOTA_BLOCK* PEPROCESS_QUOTA_BLOCK;
typedef struct _EWOW64PROCESS* PEWOW64PROCESS;
typedef struct _PO_DIAG_STACK_RECORD* PPO_DIAG_STACK_RECORD;
typedef struct _INVERTED_FUNCTION_TABLE* PINVERTED_FUNCTION_TABLE;
typedef struct _PROCESS_DISK_COUNTERS* PPROCESS_DISK_COUNTERS;
typedef struct _PO_PROCESS_ENERGY_CONTEXT* PPO_PROCESS_ENERGY_CONTEXT;

typedef struct _KAFFINITY_EX {
    USHORT          Count;
    USHORT          Size;
    ULONG           Reserved;
    SIZE_T          Bitmap[20];
} KAFFINITY_EX, * PKAFFINITY_EX;

typedef union _KEXECUTE_OPTIONS {
    union {
        struct {
            UCHAR ExecuteDisable : 1;
            UCHAR ExecuteEnable : 1;
            UCHAR DisableThunkEmulation : 1;
            UCHAR Permanent : 1;
            UCHAR ExecuteDispatchEnable : 1;
            UCHAR ImageDispatchEnable : 1;
            UCHAR DisableExceptionChainValidation : 1;
            UCHAR Spare : 1;
        };
    };
    volatile UCHAR ExecuteOptions;
    UCHAR ExecuteOptionsNV;
} KEXECUTE_OPTIONS, * PKEXECUTE_OPTIONS;

typedef union _KSTACK_COUNT {
    union {
        LONG Value;
        struct {
            ULONG State : 3;
            ULONG StackCount : 29;
        };
    };
} KSTACK_COUNT, * PKSTACK_COUNT;

typedef struct _EX_FAST_REF {
    union {
        ULONG64 Object;
        ULONG64 RefCnt : (sizeof(ULONG_PTR) == sizeof(UINT32)) ? 3 : 4;
        ULONG64 Value;
    };
} EX_FAST_REF, * PEX_FAST_REF;

typedef struct _RTL_AVL_TREE {
    struct _RTL_BALANCED_NODE* Root;
} RTL_AVL_TREE, * PRTL_AVL_TREE;

typedef struct _EX_PUSH_LOCK {
    union {
        struct {
            ULONG_PTR Locked : 1; /* bit position: 0 */
            ULONG_PTR Waiting : 1; /* bit position: 1 */
            ULONG_PTR Waking : 1; /* bit position: 2 */
            ULONG_PTR MultipleShared : 1; /* bit position: 3 */
            ULONG_PTR Shared : (sizeof(ULONG_PTR) * 8) - 4; /* bit position: 4 */
        };
        ULONG_PTR   Value;
        void* Ptr;
    };
} EX_PUSH_LOCK_IMPL, * PEX_PUSH_LOCK_IMPL;

typedef struct _PEB_LDR_DATA {
    ULONG                   Length;
    BOOLEAN                 Initialized;
    PVOID                   SsHandle;
    LIST_ENTRY              InLoadOrderModuleList;
    LIST_ENTRY              InMemoryOrderModuleList;
    LIST_ENTRY              InInitializationOrderModuleList;
} PEB_LDR_DATA, * PPEB_LDR_DATA;

typedef struct _PEB {
    BOOLEAN                               InheritedAddressSpace;
    BOOLEAN                               ReadImageFileExecOptions;
    BOOLEAN                               BeingDebugged;
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
        };
    };
#ifdef _WIN64
    UCHAR                                 Padding0[4];
#endif
    HANDLE                                Mutant;
    PVOID                                 ImageBaseAddress;
    PPEB_LDR_DATA                         Ldr;
    PRTL_USER_PROCESS_PARAMETERS          ProcessParameters;
    PVOID                                 SubSystemData;
    PVOID                                 ProcessHeap;
    PRTL_CRITICAL_SECTION                 FastPebLock;
    PVOID                                 AtlThunkSListPtr;
    PVOID                                 IFEOKey;
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
            ULONG ProcessImagesHotPatched : 1;
            ULONG ReservedBits0 : 24;
        };
    };
#ifdef _WIN64
    UCHAR                                 Padding1[4];
#endif
    union {
        PVOID KernelCallbackTable;
        PVOID UserSharedInfoPtr;
    };
    ULONG                                 SystemReserved[1];
    ULONG                                 AtlThunkSListPtr32;
    PVOID                                 ApiSetMap;
    ULONG                                 TlsExpansionCounter;
#ifdef _WIN64
    UCHAR                                 Padding2[4];
#endif
    PVOID                                 TlsBitmap;
    ULONG                                 TlsBitmapBits[2];
    PVOID                                 ReadOnlySharedMemoryBase;
    PVOID                                 SharedData;
    PVOID* ReadOnlyStaticServerData;
    PVOID                                 AnsiCodePageData;
    PVOID                                 OemCodePageData;
    PVOID                                 UnicodeCaseTableData;
    ULONG                                 NumberOfProcessors;
    ULONG                                 NtGlobalFlag;
    LARGE_INTEGER                         CriticalSectionTimeout;
    SIZE_T                                HeapSegmentReserve;
    SIZE_T                                HeapSegmentCommit;
    SIZE_T                                HeapDeCommitTotalFreeThreshold;
    SIZE_T                                HeapDeCommitFreeBlockThreshold;
    ULONG                                 NumberOfHeaps;
    ULONG                                 MaximumNumberOfHeaps;
    PVOID                                 ProcessHeaps;
    PVOID                                 GdiSharedHandleTable;
    PVOID                                 ProcessStarterHelper;
    ULONG                                 GdiDCAttributeList;
#ifdef _WIN64
    UCHAR                                 Padding3[4];
#endif
    PRTL_CRITICAL_SECTION                 LoaderLock;
    ULONG                                 OSMajorVersion;
    ULONG                                 OSMinorVersion;
    USHORT                                OSBuildNumber;
    USHORT                                OSCSDVersion;
    ULONG                                 OSPlatformId;
    ULONG                                 ImageSubsystem;
    ULONG                                 ImageSubsystemMajorVersion;
    ULONG                                 ImageSubsystemMinorVersion;
#ifdef _WIN64
    UCHAR                                 Padding4[4];
#endif
    ULONG64                               ActiveProcessAffinityMask;
    GDI_HANDLE_BUFFER                     GdiHandleBuffer;
    PVOID                                 PostProcessInitRoutine;
    PVOID                                 TlsExpansionBitmap;
    ULONG                                 TlsExpansionBitmapBits[32];
    ULONG                                 SessionId;
#ifdef _WIN64
    UCHAR                                 Padding5[4];
#endif
    ULARGE_INTEGER                        AppCompatFlags;
    ULARGE_INTEGER                        AppCompatFlagsUser;
    PVOID                                 pShimData;
    PVOID                                 AppCompatInfo;
    UNICODE_STRING                        CSDVersion;
    PACTIVATION_CONTEXT_DATA              ActivationContextData;
    PASSEMBLY_STORAGE_MAP                 ProcessAssemblyStorageMap;
    PACTIVATION_CONTEXT_DATA              SystemDefaultActivationContextData;
    PASSEMBLY_STORAGE_MAP                 SystemAssemblyStorageMap;
    SIZE_T                                MinimumStackCommit;
    PVOID* FlsCallback;
    LIST_ENTRY                            FlsListHead;
    PVOID                                 FlsBitmap;
    ULONG                                 FlsBitmapBits[FLS_MAXIMUM_AVAILABLE / (sizeof(ULONG) * 8)];
    ULONG                                 FlsHighIndex;

    PVOID                                 WerRegistrationData;
    PVOID                                 WerShipAssertPtr;
    PVOID                                 pUnused; // pContextData
    PVOID                                 pImageHeaderHash;
    union {
        ULONG TracingFlags;
        struct {
            ULONG HeapTracingEnabled : 1;
            ULONG CritSecTracingEnabled : 1;
            ULONG LibLoaderTracingEnabled : 1;
            ULONG SpareTracingBits : 29;
        } s3;
    } s4;
#ifdef _WIN64
    UCHAR                                 Padding6[4];
#endif
    ULONG64                               CsrServerReadOnlySharedMemoryBase;
    PVOID                                 TppWorkerpListLock;
    LIST_ENTRY                            TppWorkerpList;
    PVOID                                 WaitOnAddressHashTable[128];
    PVOID                                 TelemetryCoverageHeader;
    ULONG                                 CloudFileFlags;
    ULONG                                 CloudFileDiagFlags;
    UCHAR                                 PlaceholderCompatibilityMode;
    UCHAR                                 PlaceholderCompatibilityModeReserved[7];
    PLEAP_SECOND_DATA                     LeapSecondData;
    union {
        ULONG LeapSecondFlags;
        struct {
            BOOLEAN SixtySecondEnabled : 1;
            ULONG Reserved : 31;
        };
        ULONG NtGlobalFlag2;
    };
} PEB, * PPEB;

typedef struct _SE_AUDIT_PROCESS_CREATION_INFO {
    struct _OBJECT_NAME_INFORMATION* ImageFileName;
} SE_AUDIT_PROCESS_CREATION_INFO, * PSE_AUDIT_PROCESS_CREATION_INFO;

typedef struct _MMWSL_INSTANCE {
    PVOID NextPteToTrim;
    PVOID NextPteToAge;
    PVOID NextPteToAccessClear;
    ULONG LastAccessClearingRemainder;
    ULONG LastAgingRemainder;
    ULONG64 LockedEntries;
} MMWSL_INSTANCE, * PMMWSL_INSTANCE;

typedef struct _MMSUPPORT_INSTANCE {
    ULONG NextPageColor;
    ULONG PageFaultCount;
    ULONG64 TrimmedPageCount;
    PMMWSL_INSTANCE VmWorkingSetList;
    LIST_ENTRY WorkingSetExpansionLinks;
    ULONG64 AgeDistribution[8];
    PKGATE ExitOutswapGate;
    ULONG64 MinimumWorkingSetSize;
    ULONG64 WorkingSetLeafSize;
    ULONG64 WorkingSetLeafPrivateSize;
    ULONG64 WorkingSetSize;
    ULONG64 WorkingSetPrivateSize;
    ULONG64 MaximumWorkingSetSize;
    ULONG64 PeakWorkingSetSize;
    ULONG HardFaultCount;
    USHORT LastTrimStamp;
    USHORT PartitionId;
    ULONG64 SelfmapLock;
    USHORT Flags;//_MMSUPPORT_FLAGS
} MMSUPPORT_INSTANCE, * PMMSUPPORT_INSTANCE;

typedef struct _MMSUPPORT_SHARED {
    volatile LONG WorkingSetLock;
    LONG GoodCitizenWaiting;
    SIZE_T ReleasedCommitDebt;
    SIZE_T ResetPagesRepurposedCount;
    PVOID WsSwapSupport;
    PVOID CommitReleaseContext;
    PVOID AccessLog;
    volatile SIZE_T ChargedWslePages;
    SIZE_T ActualWslePages;
    SIZE_T WorkingSetCoreLock;
    PVOID ShadowMapping;
#ifdef _X86_
    LONG __UNKNOW__[14];
#else
    LONG __UNKNOW__[12];
#endif
} MMSUPPORT_SHARED, * PMMSUPPORT_SHARED;

typedef struct _MMSUPPORT_FULL {
    struct _MMSUPPORT_INSTANCE Instance;
    struct _MMSUPPORT_SHARED Shared;
} MMSUPPORT_FULL, * PMMSUPPORT_FULL;

typedef struct _ALPC_PROCESS_CONTEXT {
    EX_PUSH_LOCK Lock;
    LIST_ENTRY ViewListHead;
    volatile SIZE_T PagedPoolQuotaCache;
} ALPC_PROCESS_CONTEXT, * PALPC_PROCESS_CONTEXT;

typedef struct _PS_PROTECTION {
    union {
        UCHAR Level;
        struct {
            UCHAR Type : 3;
            UCHAR Audit : 1;
            UCHAR Signer : 4;
        };
    };
} PS_PROTECTION, * PPS_PROTECTION;

typedef union _PS_INTERLOCKED_TIMER_DELAY_VALUES {
    union {
        struct {
            ULONG64 DelayMs : 30; /* bit position: 0 */
            ULONG64 CoalescingWindowMs : 30; /* bit position: 30 */
            ULONG64 Reserved : 1; /* bit position: 60 */
            ULONG64 NewTimerWheel : 1; /* bit position: 61 */
            ULONG64 Retry : 1; /* bit position: 62 */
            ULONG64 Locked : 1; /* bit position: 63 */
        };
        ULONG64 All;
    };
} PS_INTERLOCKED_TIMER_DELAY_VALUES, * PPS_INTERLOCKED_TIMER_DELAY_VALUES;

typedef struct _JOBOBJECT_WAKE_FILTER {
    ULONG HighEdgeFilter;
    ULONG LowEdgeFilter;
} JOBOBJECT_WAKE_FILTER, * PJOBOBJECT_WAKE_FILTER;

typedef struct _PS_PROCESS_WAKE_INFORMATION {
    ULONG64 NotificationChannel;
    ULONG WakeCounters[7];
    JOBOBJECT_WAKE_FILTER WakeFilter;
    ULONG NoWakeCounter;
} PS_PROCESS_WAKE_INFORMATION, * PPS_PROCESS_WAKE_INFORMATION;

typedef struct _PS_DYNAMIC_ENFORCED_ADDRESS_RANGES {
    RTL_AVL_TREE Tree;
    EX_PUSH_LOCK Lock;
} PS_DYNAMIC_ENFORCED_ADDRESS_RANGES, * PPS_DYNAMIC_ENFORCED_ADDRESS_RANGES;

#pragma region HANDLE_TABLE

typedef struct _EXHANDLE {
    union {
        struct {
            ULONG TagBits : 2;
            ULONG Index : 30;
        };
        PVOID GenericHandleOverlay;
        ULONG64 Value;
    };
} EXHANDLE, * PEXHANDLE;

typedef struct _HANDLE_TABLE_ENTRY_INFO {
    ULONG AuditMask;
    ULONG MaxRelativeAccessMask;
} HANDLE_TABLE_ENTRY_INFO, * PHANDLE_TABLE_ENTRY_INFO;

typedef union _HANDLE_TABLE_ENTRY {
    LONG64 VolatileLowValue;
    LONG64 LowValue;
    struct {
        PHANDLE_TABLE_ENTRY_INFO InfoTable;
        union {
            LONG64 HighValue;
            union _HANDLE_TABLE_ENTRY* NextFreeHandleEntry;
            EXHANDLE LeafHandleValue;
        };
    };
    LONG64 RefCountField;
    struct {
        BOOLEAN Unlocked : 1;
        ULONG64 RefCnt : 16;
        ULONG64 Attributes : 3;
        ULONG64 ObjectPointerBits : 44;
        ULONG GrantedAccessBits : 25;
        BOOLEAN NoRightsUpgrade : 1;
        ULONG Spare1 : 6;
    };
    ULONG Spare2;
} HANDLE_TABLE_ENTRY, * PHANDLE_TABLE_ENTRY;

typedef struct _HANDLE_TABLE_FREE_LIST {
    EX_PUSH_LOCK FreeListLock;
    PHANDLE_TABLE_ENTRY FirstFreeHandleEntry;
    PHANDLE_TABLE_ENTRY LastFreeHandleEntry;
    LONG HandleCount;
    ULONG HighWaterMark;
} HANDLE_TABLE_FREE_LIST, * PHANDLE_TABLE_FREE_LIST;

typedef struct _HANDLE_TRACE_DB_ENTRY {
    CLIENT_ID ClientId;
    PVOID Handle;
    ULONG Type;
    PVOID StackTrace[16];
} HANDLE_TRACE_DB_ENTRY, * PHANDLE_TRACE_DB_ENTRY;

typedef struct _HANDLE_TRACE_DEBUG_INFO {
    LONG RefCount;
    ULONG TableSize;
    ULONG BitMaskFlags;
    FAST_MUTEX CloseCompactionLock;
    ULONG CurrentStackIndex;
    HANDLE_TRACE_DB_ENTRY TraceDb[1];
} HANDLE_TRACE_DEBUG_INFO, * PHANDLE_TRACE_DEBUG_INFO;

typedef struct _HANDLE_TABLE {
    ULONG NextHandleNeedingPool;
    LONG ExtraInfoPages;
    ULONG64 TableCode;
    PEPROCESS QuotaProcess;
    LIST_ENTRY HandleTableList;
    ULONG UniqueProcessId;
    union {
        ULONG Flags;
        struct {
            ULONG StrictFIFO : 1;
            ULONG EnableHandleExceptions : 1;
            ULONG Rundown : 1;
            ULONG Duplicated : 1;
            ULONG RaiseUMExceptionOnInvalidHandleClose : 1;
        };
    };
    EX_PUSH_LOCK HandleContentionEvent;
    EX_PUSH_LOCK HandleTableLock;
    union {
        HANDLE_TABLE_FREE_LIST FreeLists[1];
        struct {
            UCHAR  ActualEntry[32];
            PHANDLE_TRACE_DEBUG_INFO DebugInfo;
        };
    };
} HANDLE_TABLE, * PHANDLE_TABLE;

#pragma endregion

#pragma region KGDTENTRY

typedef struct _KGDTENTRY32 {
    USHORT     LimitLow;
    USHORT     BaseLow;
    union {
        union {
            struct {
                UCHAR BaseMid;
                UCHAR Flags1;
                UCHAR Flags2;
                UCHAR BaseHi;
            } Bytes;
            struct {
                struct {
                    ULONG BaseMid : 8; /* bit position: 0 */
                    ULONG Type : 5; /* bit position: 8 */
                    ULONG Dpl : 2; /* bit position: 13 */
                    ULONG Pres : 1; /* bit position: 15 */
                    ULONG LimitHi : 4; /* bit position: 16 */
                    ULONG Sys : 1; /* bit position: 20 */
                    ULONG Reserved_0 : 1; /* bit position: 21 */
                    ULONG Default_Big : 1; /* bit position: 22 */
                    ULONG Granularity : 1; /* bit position: 23 */
                    ULONG BaseHi : 8; /* bit position: 24 */
                };
            } Bits;
        };
    } HighWord;
} KGDTENTRY32, * PKGDTENTRY32;

typedef struct _KGDTENTRY64 {
    union {
        struct {
            USHORT LimitLow;
            USHORT BaseLow;
            union {
                struct {
                    UCHAR BaseMiddle;
                    UCHAR Flags1;
                    UCHAR Flags2;
                    UCHAR BaseHigh;
                } Bytes;
                struct {
                    struct {
                        ULONG BaseMiddle : 8; /* bit position: 0 */
                        ULONG Type : 5; /* bit position: 8 */
                        ULONG Dpl : 2; /* bit position: 13 */
                        ULONG Present : 1; /* bit position: 15 */
                        ULONG LimitHigh : 4; /* bit position: 16 */
                        ULONG System : 1; /* bit position: 20 */
                        ULONG LongMode : 1; /* bit position: 21 */
                        ULONG DefaultBig : 1; /* bit position: 22 */
                        ULONG Granularity : 1; /* bit position: 23 */
                        ULONG BaseHigh : 8; /* bit position: 24 */
                    } Bits;
                    ULONG BaseUpper;
                    ULONG MustBeZero;
                };
            };
        };
        struct {
            LONG64 DataLow;
            LONG64 DataHigh;
        };
    };
} KGDTENTRY64, * PKGDTENTRY64;

#ifdef _WIN64
typedef KGDTENTRY64 KGDTENTRY;
typedef PKGDTENTRY64 PKGDTENTRY;
#else
typedef KGDTENTRY32 KGDTENTRY;
typedef PKGDTENTRY32 PKGDTENTRY;
#endif

#pragma endregion

#pragma region KIDTENTRY

typedef struct _KIDTENTRY32 {
    USHORT Offset;
    USHORT Selector;
    USHORT Access;
    USHORT ExtendedOffset;
} KIDTENTRY32, * PKIDTENTRY32;

typedef union _KIDTENTRY64 {
    union {
        struct {
            USHORT OffsetLow;
            USHORT Selector;
            struct {
                USHORT IstIndex : 3; /* bit position: 0 */
                USHORT Reserved0 : 5; /* bit position: 3 */
                USHORT Type : 5; /* bit position: 8 */
                USHORT Dpl : 2; /* bit position: 13 */
                USHORT Present : 1; /* bit position: 15 */
            };
            USHORT OffsetMiddle;
            ULONG OffsetHigh;
            ULONG Reserved1;
        };
        ULONG64 Alignment;
    };
} KIDTENTRY64, * PKIDTENTRY64;

#ifdef _WIN64
typedef KIDTENTRY64 KIDTENTRY;
typedef PKIDTENTRY64 PKIDTENTRY;
#else
typedef KIDTENTRY32 KIDTENTRY;
typedef PKIDTENTRY32 PKIDTENTRY;
#endif

#pragma endregion

#pragma region KPROCESS

typedef struct _KPROCESS {
    DISPATCHER_HEADER                   Header;
    LIST_ENTRY                          ProfileListHead;
    PVOID                               DirectoryTableBase;
#ifdef _X86_
    KGDTENTRY                           LdtDescriptor;
    KIDTENTRY                           Int21Descriptor;
#endif
    LIST_ENTRY                          ThreadListHead;
    ULONG                               ProcessLock;
#ifdef _WIN64
    ULONG                               ProcessTimerDelay;
#endif
    ULONG64                             DeepFreezeStartTime;
    KAFFINITY_EX                        Affinity;
#ifdef _WIN64
    ULONG64                             AffinityPadding[12];
#endif
    LIST_ENTRY                          ReadyListHead;
    SINGLE_LIST_ENTRY                   SwapListEntry;
    KAFFINITY_EX                        ActiveProcessors;
#ifdef _WIN64
    ULONG64                             ActiveProcessorsPadding[12];
#endif
    union {
        struct {
            ULONG AutoAlignment : 1;
            ULONG DisableBoost : 1;
            ULONG DisableQuantum : 1;
            ULONG DeepFreeze : 1;
            ULONG TimerVirtualization : 1;
            ULONG CheckStackExtents : 1;
            ULONG CacheIsolationEnabled : 1;
            ULONG PpmPolicy : 3;
            ULONG VaSpaceDeleted : 1;
            ULONG ReservedFlags : (sizeof(UINT32) * 8) - 11;
        };
        ULONG ProcessFlags;
    };
#ifdef _WIN64
    ULONG                                 ActiveGroupsMask;
#endif
    CHAR                                  BasePriority;
    CHAR                                  QuantumReset;
    CHAR                                  Visited;
    KEXECUTE_OPTIONS                      Flags;
    USHORT                                ThreadSeed[20];
#ifdef _WIN64
    USHORT                                ThreadSeedPadding[12];
#endif
    USHORT                                IdealProcessor[20];
#ifdef _WIN64
    USHORT                                IdealProcessorPadding[12];
#endif
    USHORT                                IdealNode[20];
#ifdef _WIN64
    USHORT                                IdealNodePadding[12];
#endif
    USHORT                                IdealGlobalNode;
    USHORT                                Spare1;
#ifdef _X86_
    UINT16                                IopmOffset;
    PKSCHEDULING_GROUP                    SchedulingGroup;
#endif
    KSTACK_COUNT                          StackCount;
    LIST_ENTRY                            ProcessListEntry;
    ULONG64                               CycleTime;
    ULONG64                               ContextSwitches;
#ifdef _WIN64
    PKSCHEDULING_GROUP                    SchedulingGroup;
#endif
    ULONG                                 FreezeCount;
    ULONG                                 KernelTime;
    ULONG                                 UserTime;
    ULONG                                 ReadyTime;
#ifdef _WIN64
    ULONG64                               UserDirectoryTableBase;
    UCHAR                                 AddressPolicy;
    UCHAR                                 Spare2[71];
    PVOID                                 InstrumentationCallback;
    union {
        union {
            ULONG64 SecureHandle;
            struct {
                struct {
                    ULONG64 SecureProcess : 1;
                    ULONG64 Unused : 1;
                };
            } Flags;
        };
    } SecureState;
#else
    PVOID                                 VdmTrapcHandler;
    ULONG                                 ProcessTimerDelay;
#endif
    ULONG64                               KernelWaitTime;
    ULONG64                               UserWaitTime;
    SIZE_T                                EndPadding[8];
} KPROCESS, * PKPROCESS;

#pragma endregion

#pragma region EPROCESS

typedef struct _EPROCESS {
    KPROCESS                              Pcb;
    EX_PUSH_LOCK_IMPL                     ProcessLock;
    PVOID                                 UniqueProcessId;
    LIST_ENTRY                            ActiveProcessLinks;
    EX_RUNDOWN_REF                        RundownProtect;
#ifdef _X86_
    PVOID                                 VdmObjects;
#endif
    union {
        ULONG Flags2;
        struct {
            ULONG JobNotReallyActive : 1;              /* bit position: 0 */
            ULONG AccountingFolded : 1;                /* bit position: 1 */
            ULONG NewProcessReported : 1;              /* bit position: 2 */
            ULONG ExitProcessReported : 1;             /* bit position: 3 */
            ULONG ReportCommitChanges : 1;             /* bit position: 4 */
            ULONG LastReportMemory : 1;                /* bit position: 5 */
            ULONG ForceWakeCharge : 1;                 /* bit position: 6 */
            ULONG CrossSessionCreate : 1;              /* bit position: 7 */
            ULONG NeedsHandleRundown : 1;              /* bit position: 8 */
            ULONG RefTraceEnabled : 1;                 /* bit position: 9 */
            ULONG PicoCreated : 1;                     /* bit position: 10 */
            ULONG EmptyJobEvaluated : 1;               /* bit position: 11 */
            ULONG DefaultPagePriority : 3;             /* bit position: 12 */
            ULONG PrimaryTokenFrozen : 1;              /* bit position: 15 */
            ULONG ProcessVerifierTarget : 1;           /* bit position: 16 */
            ULONG RestrictSetThreadContext : 1;        /* bit position: 17 */
            ULONG AffinityPermanent : 1;               /* bit position: 18 */
            ULONG AffinityUpdateEnable : 1;            /* bit position: 19 */
            ULONG PropagateNode : 1;                   /* bit position: 20 */
            ULONG ExplicitAffinity : 1;                /* bit position: 21 */
            ULONG ProcessExecutionState : 2;           /* bit position: 22 */
            ULONG EnableReadVmLogging : 1;             /* bit position: 24 */
            ULONG EnableWriteVmLogging : 1;            /* bit position: 25 */
            ULONG FatalAccessTerminationRequested : 1; /* bit position: 26 */
            ULONG DisableSystemAllowedCpuSet : 1;      /* bit position: 27 */
            ULONG ProcessStateChangeRequest : 2;       /* bit position: 28 */
            ULONG ProcessStateChangeInProgress : 1;    /* bit position: 30 */
            ULONG InPrivate : 1;                       /* bit position: 31 */
        };
};
    union {
        ULONG Flags;
        struct {
            ULONG CreateReported : 1;               /* bit position: 0 */
            ULONG NoDebugInherit : 1;               /* bit position: 1 */
            ULONG ProcessExiting : 1;               /* bit position: 2 */
            ULONG ProcessDelete : 1;                /* bit position: 3 */
            ULONG ManageExecutableMemoryWrites : 1; /* bit position: 4 */
            ULONG VmDeleted : 1;                    /* bit position: 5 */
            ULONG OutswapEnabled : 1;               /* bit position: 6 */
            ULONG Outswapped : 1;                   /* bit position: 7 */
            ULONG FailFastOnCommitFail : 1;         /* bit position: 8 */
            ULONG Wow64VaSpace4Gb : 1;              /* bit position: 9 */
            ULONG AddressSpaceInitialized : 2;      /* bit position: 10 */
            ULONG SetTimerResolution : 1;           /* bit position: 12 */
            ULONG BreakOnTermination : 1;           /* bit position: 13 */
            ULONG DeprioritizeViews : 1;            /* bit position: 14 */
            ULONG WriteWatch : 1;                   /* bit position: 15 */
            ULONG ProcessInSession : 1;             /* bit position: 16 */
            ULONG OverrideAddressSpace : 1;         /* bit position: 17 */
            ULONG HasAddressSpace : 1;              /* bit position: 18 */
            ULONG LaunchPrefetched : 1;             /* bit position: 19 */
            ULONG Background : 1;                   /* bit position: 20 */
            ULONG VmTopDown : 1;                    /* bit position: 21 */
            ULONG ImageNotifyDone : 1;              /* bit position: 22 */
            ULONG PdeUpdateNeeded : 1;              /* bit position: 23 */
            ULONG VdmAllowed : 1;                   /* bit position: 24 */
            ULONG ProcessRundown : 1;               /* bit position: 25 */
            ULONG ProcessInserted : 1;              /* bit position: 26 */
            ULONG DefaultIoPriority : 3;            /* bit position: 27 */
            ULONG ProcessSelfDelete : 1;            /* bit position: 30 */
            ULONG SetTimerResolutionLink : 1;       /* bit position: 31 */
        };
    };
    LARGE_INTEGER                         CreateTime;
    SIZE_T                                ProcessQuotaUsage[2];
    SIZE_T                                ProcessQuotaPeak[2];
    SIZE_T                                PeakVirtualSize;
    SIZE_T                                VirtualSize;
    LIST_ENTRY                            SessionProcessLinks;
    union {
        PVOID ExceptionPortData;
        SIZE_T ExceptionPortValue;
        SIZE_T ExceptionPortState : 3;
    };
    EX_FAST_REF                           Token;
    SIZE_T                                MmReserved;
    EX_PUSH_LOCK                          AddressCreationLock;
    EX_PUSH_LOCK                          PageTableCommitmentLock;
    PETHREAD                              RotateInProgress;
    PETHREAD                              ForkInProgress;
    PEJOB                                 CommitChargeJob;
    RTL_AVL_TREE                          CloneRoot;
    volatile SIZE_T                       NumberOfPrivatePages;
    volatile SIZE_T                       NumberOfLockedPages;
    PVOID                                 Win32Process;
    volatile PEJOB                        Job;
    PVOID                                 SectionObject;
    PVOID                                 SectionBaseAddress;
    ULONG                                 Cookie;
    PPAGEFAULT_HISTORY                    WorkingSetWatch;
    PVOID                                 Win32WindowStation;
    PVOID                                 InheritedFromUniqueProcessId;
#ifdef _X86_
    PVOID                                 LdtInformation;
#endif
    volatile SIZE_T                       OwnerProcessId;
    PPEB                                  Peb;
    PMM_SESSION_SPACE                     Session;
    PVOID                                 Spare1;
    PEPROCESS_QUOTA_BLOCK                 QuotaBlock;
    PHANDLE_TABLE                         ObjectTable;
    PVOID                                 DebugPort;
#ifdef _WIN64
    PEWOW64PROCESS                        WoW64Process;
#else
    PVOID                                 PaeTop;
#endif
    PVOID                                 DeviceMap;
    PVOID                                 EtwDataSource;
    ULONG64                               PageDirectoryPte;
    PFILE_OBJECT                          ImageFilePointer;
    UCHAR                                 ImageFileName[15];
    UCHAR                                 PriorityClass;
    PVOID                                 SecurityPort;
    SE_AUDIT_PROCESS_CREATION_INFO        SeAuditProcessCreationInfo;
    LIST_ENTRY                            JobLinks;
    PVOID                                 HighestUserAddress;
    LIST_ENTRY                            ThreadListHead;
    ULONG                                 ActiveThreads;
    ULONG                                 ImagePathHash;
    ULONG                                 DefaultHardErrorProcessing;
    LONG                                  LastThreadExitStatus;
    EX_FAST_REF                           PrefetchTrace;
    PVOID                                 LockedPagesList;
    LARGE_INTEGER                         ReadOperationCount;
    LARGE_INTEGER                         WriteOperationCount;
    LARGE_INTEGER                         OtherOperationCount;
    LARGE_INTEGER                         ReadTransferCount;
    LARGE_INTEGER                         WriteTransferCount;
    LARGE_INTEGER                         OtherTransferCount;
    ULONG64                               CommitChargeLimit;
    ULONG64                               CommitCharge;
    ULONG64                               CommitChargePeak;
    PVOID                                 __UNKNOW__[5];
    MMSUPPORT_FULL                        Vm;
    LIST_ENTRY                            MmProcessLinks;
    ULONG                                 ModifiedPageCount;
    ULONG                                 ExitStatus;
    RTL_AVL_TREE                          VadRoot;
    PVOID                                 VadHint;
    ULONG64                               VadCount;
    ULONG64                               VadPhysicalPages;
    ULONG64                               VadPhysicalPagesLimit;
    ALPC_PROCESS_CONTEXT                  AlpcContext;
    LIST_ENTRY                            TimerResolutionLink;
    PPO_DIAG_STACK_RECORD                 TimerResolutionStackRecord;
    ULONG                                 RequestedTimerResolution;
    ULONG                                 SmallestTimerResolution;
    LARGE_INTEGER                         ExitTime;
#ifdef _WIN64
    PINVERTED_FUNCTION_TABLE              InvertedFunctionTable;
    EX_PUSH_LOCK                          InvertedFunctionTableLock;
#endif
    ULONG                                 ActiveThreadsHighWatermark;
    ULONG                                 LargePrivateVadCount;
    EX_PUSH_LOCK                          ThreadListLock;
    PVOID                                 WnfContext;
    PEJOB                                 ServerSilo;
    UCHAR                                 SignatureLevel;
    UCHAR                                 SectionSignatureLevel;
    PS_PROTECTION                         Protection;
    struct {
        UCHAR HangCount : 3;          /* bit position: 0 */
        UCHAR GhostCount : 3;         /* bit position: 3 */
        UCHAR PrefilterException : 1; /* bit position: 6 */
    };
    union {
        UINT32 Flags3;
        struct {
            UINT32 Minimal : 1;                           /* bit position: 0 */
            UINT32 ReplacingPageRoot : 1;                 /* bit position: 1 */
            UINT32 Crashed : 1;                           /* bit position: 2 */
            UINT32 JobVadsAreTracked : 1;                 /* bit position: 3 */
            UINT32 VadTrackingDisabled : 1;               /* bit position: 4 */
            UINT32 AuxiliaryProcess : 1;                  /* bit position: 5 */
            UINT32 SubsystemProcess : 1;                  /* bit position: 6 */
            UINT32 IndirectCpuSets : 1;                   /* bit position: 7 */
            UINT32 RelinquishedCommit : 1;                /* bit position: 8 */
            UINT32 HighGraphicsPriority : 1;              /* bit position: 9 */
            UINT32 CommitFailLogged : 1;                  /* bit position: 10 */
            UINT32 ReserveFailLogged : 1;                 /* bit position: 11 */
            UINT32 SystemProcess : 1;                     /* bit position: 12 */
            UINT32 HideImageBaseAddresses : 1;            /* bit position: 13 */
            UINT32 AddressPolicyFrozen : 1;               /* bit position: 14 */
            UINT32 ProcessFirstResume : 1;                /* bit position: 15 */
            UINT32 ForegroundExternal : 1;                /* bit position: 16 */
            UINT32 ForegroundSystem : 1;                  /* bit position: 17 */
            UINT32 HighMemoryPriority : 1;                /* bit position: 18 */
            UINT32 EnableProcessSuspendResumeLogging : 1; /* bit position: 19 */
            UINT32 EnableThreadSuspendResumeLogging : 1;  /* bit position: 20 */
            UINT32 SecurityDomainChanged : 1;             /* bit position: 21 */
            UINT32 SecurityFreezeComplete : 1;            /* bit position: 22 */
            UINT32 VmProcessorHost : 1;                   /* bit position: 23 */
            UINT32 VmProcessorHostTransition : 1;         /* bit position: 24 */
            UINT32 AltSyscall : 1;                        /* bit position: 25 */
            UINT32 TimerResolutionIgnore : 1;             /* bit position: 26 */
#if _WIN64
            UINT32 DisallowUserTerminate : 1;             /* bit position: 27 */
#endif
        };                                                /* bitfield */
    };
    LONG                                  DeviceAsid;
    PVOID                                 SvmData;
    EX_PUSH_LOCK                          SvmProcessLock;
    ULONG64                               SvmLock;
    LIST_ENTRY                            SvmProcessDeviceListHead;
    ULONG64                               LastFreezeInterruptTime;
    PPROCESS_DISK_COUNTERS                DiskCounters;
    PVOID                                 PicoContext;
#ifdef _WIN64
    PVOID                                 EnclaveTable;
    ULONG64                               EnclaveNumber;
    EX_PUSH_LOCK                          EnclaveLock;
#endif 
    ULONG                                 HighPriorityFaultsAllowed;
#ifdef _X86_
    PVOID                                 InstrumentationCallback;
#endif
    PPO_PROCESS_ENERGY_CONTEXT            EnergyContext;
    PVOID                                 VmContext;
    ULONG64                               SequenceNumber;
    ULONG64                               CreateInterruptTime;
    ULONG64                               CreateUnbiasedInterruptTime;
    ULONG64                               TotalUnbiasedFrozenTime;
    ULONG64                               LastAppStateUpdateTime;
    struct {
        UINT64 LastAppStateUptime : 61; /* bit position: 0 */
        UINT64 LastAppState : 3;        /* bit position: 61 */
    };
    ULONG64                               SharedCommitCharge;
    EX_PUSH_LOCK                          SharedCommitLock;
    LIST_ENTRY                            SharedCommitLinks;
    union {
        struct {
            ULONG64 AllowedCpuSets;
            ULONG64 DefaultCpuSets;
        };
        struct {
            PVOID AllowedCpuSetsIndirect;
            PVOID DefaultCpuSetsIndirect;
        };
    };
    PVOID                                 DiskIoAttribution;
    PVOID                                 DxgProcess;
    ULONG                                 Win32KFilterSet;
    PS_INTERLOCKED_TIMER_DELAY_VALUES     ProcessTimerDelay;
    ULONG                                 KTimerSets;
    ULONG                                 KTimer2Sets;
    ULONG                                 ThreadTimerSets;
    ULONG64                               VirtualTimerListLock;
    LIST_ENTRY                            VirtualTimerListHead;
    union {
        WNF_STATE_NAME WakeChannel;
        PS_PROCESS_WAKE_INFORMATION WakeInfo;
    };
    union {
        UINT32 MitigationFlags;
        struct {
            struct {
                UINT32 ControlFlowGuardEnabled : 1;                      /* bit position: 0 */
                UINT32 ControlFlowGuardExportSuppressionEnabled : 1;     /* bit position: 1 */
                UINT32 ControlFlowGuardStrict : 1;                       /* bit position: 2 */
                UINT32 DisallowStrippedImages : 1;                       /* bit position: 3 */
                UINT32 ForceRelocateImages : 1;                          /* bit position: 4 */
                UINT32 HighEntropyASLREnabled : 1;                       /* bit position: 5 */
                UINT32 StackRandomizationDisabled : 1;                   /* bit position: 6 */
                UINT32 ExtensionPointDisable : 1;                        /* bit position: 7 */
                UINT32 DisableDynamicCode : 1;                           /* bit position: 8 */
                UINT32 DisableDynamicCodeAllowOptOut : 1;                /* bit position: 9 */
                UINT32 DisableDynamicCodeAllowRemoteDowngrade : 1;       /* bit position: 10 */
                UINT32 AuditDisableDynamicCode : 1;                      /* bit position: 11 */
                UINT32 DisallowWin32kSystemCalls : 1;                    /* bit position: 12 */
                UINT32 AuditDisallowWin32kSystemCalls : 1;               /* bit position: 13 */
                UINT32 EnableFilteredWin32kAPIs : 1;                     /* bit position: 14 */
                UINT32 AuditFilteredWin32kAPIs : 1;                      /* bit position: 15 */
                UINT32 DisableNonSystemFonts : 1;                        /* bit position: 16 */
                UINT32 AuditNonSystemFontLoading : 1;                    /* bit position: 17 */
                UINT32 PreferSystem32Images : 1;                         /* bit position: 18 */
                UINT32 ProhibitRemoteImageMap : 1;                       /* bit position: 19 */
                UINT32 AuditProhibitRemoteImageMap : 1;                  /* bit position: 20 */
                UINT32 ProhibitLowILImageMap : 1;                        /* bit position: 21 */
                UINT32 AuditProhibitLowILImageMap : 1;                   /* bit position: 22 */
                UINT32 SignatureMitigationOptIn : 1;                     /* bit position: 23 */
                UINT32 AuditBlockNonMicrosoftBinaries : 1;               /* bit position: 24 */
                UINT32 AuditBlockNonMicrosoftBinariesAllowStore : 1;     /* bit position: 25 */
                UINT32 LoaderIntegrityContinuityEnabled : 1;             /* bit position: 26 */
                UINT32 AuditLoaderIntegrityContinuity : 1;               /* bit position: 27 */
                UINT32 EnableModuleTamperingProtection : 1;              /* bit position: 28 */
                UINT32 EnableModuleTamperingProtectionNoInherit : 1;     /* bit position: 29 */
                UINT32 RestrictIndirectBranchPrediction : 1;             /* bit position: 30 */
                UINT32 IsolateSecurityDomain : 1;                        /* bit position: 31 */
            };
        } MitigationFlagsValues;
    };
    union {
        UINT32 MitigationFlags2;
        struct {
            struct {
                UINT32 EnableExportAddressFilter : 1;                   /* bit position: 0 */
                UINT32 AuditExportAddressFilter : 1;                    /* bit position: 1 */
                UINT32 EnableExportAddressFilterPlus : 1;               /* bit position: 2 */
                UINT32 AuditExportAddressFilterPlus : 1;                /* bit position: 3 */
                UINT32 EnableRopStackPivot : 1;                         /* bit position: 4 */
                UINT32 AuditRopStackPivot : 1;                          /* bit position: 5 */
                UINT32 EnableRopCallerCheck : 1;                        /* bit position: 6 */
                UINT32 AuditRopCallerCheck : 1;                         /* bit position: 7 */
                UINT32 EnableRopSimExec : 1;                            /* bit position: 8 */
                UINT32 AuditRopSimExec : 1;                             /* bit position: 9 */
                UINT32 EnableImportAddressFilter : 1;                   /* bit position: 10 */
                UINT32 AuditImportAddressFilter : 1;                    /* bit position: 11 */
                UINT32 DisablePageCombine : 1;                          /* bit position: 12 */
                UINT32 SpeculativeStoreBypassDisable : 1;               /* bit position: 13 */
                UINT32 CetShadowStacks : 1;                             /* bit position: 14 */
            };
        } MitigationFlags2Values;
    };
    PVOID                                 PartitionObject;
    ULONG64                               SecurityDomain;
    ULONG64                               ParentSecurityDomain;
    PVOID                                 CoverageSamplerContext;
    PVOID                                 MmHotPatchContext;
    RTL_AVL_TREE                          DynamicEHContinuationTargetsTree;
    EX_PUSH_LOCK                          DynamicEHContinuationTargetsLock;
    PS_DYNAMIC_ENFORCED_ADDRESS_RANGES    DynamicEnforcedCetCompatibleRanges;
    ULONG                                 DisabledComponentFlags;
    PVOID                                 PathRedirectionHashes;
} EPROCESS;

#pragma endregion

#pragma region LDR_DATA
#ifdef _WIN64
typedef struct _LDR_DATA {
    LIST_ENTRY			ListEntry;
    ULONG64				__Undefined1;
    ULONG64				__Undefined2;
    ULONG64				__Undefined3;
    ULONG64				NonPagedDebugInfo;
    ULONG64				DllBase;
    ULONG64				EntryPoint;
    ULONG				SizeOfImage;
    UNICODE_STRING		Path;
    UNICODE_STRING		Name;
    ULONG				Flags;
}LDR_DATA, * PLDR_DATA;
#else
typedef struct _LDR_DATA {
    LIST_ENTRY			ListEntry;
    ULONG				unknown1;
    ULONG				unknown2;
    ULONG				unknown3;
    ULONG				unknown4;
    ULONG				unknown5;
    ULONG				unknown6;
    ULONG				unknown7;
    UNICODE_STRING		Path;
    UNICODE_STRING		Name;
    ULONG				Flags;
}LDR_DATA, * PLDR_DATA;
#endif
#pragma endregion

#endif // !__HELL_DRIVER_STRUCT_HEADER__