#include "FetchHook.h"
#define DRIVERNAME_SIZE        1024
static ULONG g_Tag = 'ssdt';
ULONG NtBuildNumber = 0;
ULONG ObjectCallbackListOffset = 0;

PVOID GetPsLoadedListModules();
BOOLEAN GetVersionAndHardCode();
PVOID GetCallPoint(PVOID pCallPoint);
BOOLEAN GetDriverNameByPoint(PVOID pPoint, PWCHAR pDriverName);
PVOID GetUndocumentFunctionAddress(IN PUNICODE_STRING pFunName, IN PUCHAR pStartAddress, IN UCHAR* pFeatureCode, IN ULONG pFeatureCodeNum, ULONG pSerSize, UCHAR pSegCode, LONG pAddNum, BOOLEAN pByName);


ULONG EnumRegisterHookCallBacks() {
    ULONG count = 0;
    ULONG tcount = 0;
    PLIST_ENTRY curr = NULL;
    POB_CALLBACK back;
    GetVersionAndHardCode();

    PWCHAR driverName;
    ULONG64 ObProcessCallbackListHead = *(ULONG64*)PsProcessType + ObjectCallbackListOffset;
    ULONG64 ObThreadCallbackListHead = *(ULONG64*)PsThreadType + ObjectCallbackListOffset;
    curr = ((PLIST_ENTRY)ObProcessCallbackListHead)->Flink;
    if (curr == NULL || !MmIsAddressValid(curr)) {
        return count;
    }

    driverName = (PWCHAR)ExAllocatePool2(POOL_FLAG_NON_PAGED, DRIVERNAME_SIZE, g_Tag);
    if (driverName == NULL) {
        return count;
    }
    RtlZeroMemory(driverName, DRIVERNAME_SIZE);
    do {
        back = (POB_CALLBACK)curr;
        if (back->ObHandle != 0) {
            if (GetDriverNameByPoint((PVOID)back->PreCall, driverName)) {
                HLog("进程 已加载: Handle:%p    %-10wZ    驱动名:%S", back->ObHandle, &back->ObHandle->AltitudeString, driverName);
                count++;
            }
        }
        curr = curr->Flink;
    } while (curr != (PLIST_ENTRY)ObProcessCallbackListHead);
    curr = ((PLIST_ENTRY)ObThreadCallbackListHead)->Flink;
    if (curr == NULL || !MmIsAddressValid(curr)) {
        return count;
    }
    HLog("----------------------------------------------------- 进程钩子: %d 个 ---------------------------------------------------", count);
    do {
        back = (POB_CALLBACK)curr;
        if (back->ObHandle != 0) {
            if (GetDriverNameByPoint((PVOID)back->PreCall, driverName)) {
                HLog("线程 已加载: Handle:%p    %-10wZ    驱动名:%S", back->ObHandle, &back->ObHandle->AltitudeString, driverName);
                tcount++;
            }
        }
        curr = curr->Flink;
    } while (curr != (PLIST_ENTRY)ObThreadCallbackListHead);
    HLog("----------------------------------------------------- 线程钩子: %d 个 ---------------------------------------------------", tcount);
    return count + tcount;
}

BOOLEAN GetDriverNameByPoint(PVOID pPoint, PWCHAR pDriverName) {
    if (pDriverName == NULL) {
        return FALSE;
    }
    PLDR_DATA_TABLE_ENTRY begin = NULL;
    PLIST_ENTRY head = NULL;
    PLIST_ENTRY next = NULL;
    begin = GetPsLoadedListModules();
    if (begin == NULL) {
        return FALSE;
    }
    head = begin->InLoadOrderLinks.Flink;
    next = head->Flink;
    do {
        PLDR_DATA_TABLE_ENTRY entry = CONTAINING_RECORD(next, LDR_DATA_TABLE_ENTRY, InLoadOrderLinks);
        next = next->Flink;
        if ((ULONG_PTR)entry->DllBase <= (ULONG_PTR)pPoint && (ULONG_PTR)pPoint <= ((ULONG_PTR)entry->DllBase + entry->SizeOfImage)) {
            RtlZeroMemory(pDriverName, DRIVERNAME_SIZE);
            RtlCopyMemory(pDriverName, entry->BaseDllName.Buffer, entry->BaseDllName.Length);
            return TRUE;
        }
    } while (next != head->Flink);
    return FALSE;
}

PVOID GetPsLoadedListModules() {
    UNICODE_STRING RtlPcToFileHeader = RTL_CONSTANT_STRING(L"RtlPcToFileHeader");
    UNICODE_STRING PsLoadedModuleList = RTL_CONSTANT_STRING(L"PsLoadedModuleList");
    PVOID point = NULL;
    static PVOID PsLoadedListModule = NULL;
    UCHAR shellcode[11] = "\x48\x8B\x0D\x60\x60\x60\x60\x48\x85\xC9";
    if (PsLoadedListModule) {
        return PsLoadedListModule;
    }
    if (NtBuildNumber > 9600) {
        PsLoadedListModule = MmGetSystemRoutineAddress(&PsLoadedModuleList);
        return PsLoadedListModule;
    }
    point = GetUndocumentFunctionAddress(&RtlPcToFileHeader, NULL, shellcode, 10, 0xFF, 0x60, 0, TRUE);
    if (point == NULL || !MmIsAddressValid(point)) {
        return NULL;
    }
    point = GetCallPoint(point);
    if (point == NULL || !MmIsAddressValid(point)) {
        return NULL;
    }
    PsLoadedListModule = point;
    return PsLoadedListModule;
}

PVOID GetUndocumentFunctionAddress(IN PUNICODE_STRING pFunName, IN PUCHAR pStartAddress, IN UCHAR* pFeatureCode, IN ULONG pFeatureCodeNum, ULONG pSerSize, UCHAR pSegCode, LONG pAddNum, BOOLEAN pByName) {
    ULONG dwIndex = 0;
    PUCHAR pFunAddress = NULL;
    ULONG dwCodeNum = 0;
    if (pFeatureCode == NULL) {
        return NULL;
    }
    if (pFeatureCodeNum >= 50) {
        return NULL;
    }
    if (pByName) {
        if (pFunName == NULL || !MmIsAddressValid((PVOID)pFunName)) {
            return NULL;
        }
        pFunAddress = (PUCHAR)MmGetSystemRoutineAddress(pFunName);
        if (pFunAddress == NULL) {
            return NULL;
        }
    } else {
        if (pStartAddress == NULL || !MmIsAddressValid(pStartAddress)) {
            HLog("invalid start address:%p\n", pStartAddress);
            return NULL;
        }
        pFunAddress = pStartAddress;
    }
    for (dwIndex = 0; dwIndex < pSerSize; dwIndex++) {
        __try {
            if (!MmIsAddressValid(pFunAddress + dwIndex)) {
                return 0;
            }
            if (pFunAddress[dwIndex] == pFeatureCode[dwCodeNum] || pFeatureCode[dwCodeNum] == pSegCode) {
                dwCodeNum++;
                if (dwCodeNum == pFeatureCodeNum) {
                    return pFunAddress + dwIndex - dwCodeNum + 1 + pAddNum;
                }
                continue;
            }
            if (dwCodeNum) {
                dwIndex = dwIndex - dwCodeNum + 1;
            }
            dwCodeNum = 0;
        } __except (EXCEPTION_EXECUTE_HANDLER) {
            HLog("exp %p\n", pFunAddress + dwIndex);
            return 0;
        }
    }
    return 0;
}

PVOID GetCallPoint(PVOID pCallPoint) {
    ULONG dwOffset = 0;
    ULONG_PTR returnAddress = 0;
    LARGE_INTEGER returnAddressTemp = { 0 };
    PUCHAR pFunAddress = NULL;
    if (pCallPoint == NULL || !MmIsAddressValid(pCallPoint)) {
        return NULL;
    }
    pFunAddress = pCallPoint;
    RtlCopyMemory(&dwOffset, (PVOID)(pFunAddress + 1), sizeof(ULONG));
    if ((dwOffset & 0x10000000) == 0x10000000) {
        dwOffset = dwOffset + 5 + (ULONG)(ULONG_PTR)pFunAddress;
        returnAddressTemp.QuadPart = (ULONG_PTR)pFunAddress & 0xFFFFFFFF00000000;
        returnAddressTemp.LowPart = dwOffset;
        returnAddress = returnAddressTemp.QuadPart;
        return (PVOID)returnAddress;
    }
    returnAddress = (ULONG_PTR)dwOffset + 5 + (ULONG)(ULONG_PTR)pFunAddress;
    return (PVOID)returnAddress;
}

BOOLEAN GetVersionAndHardCode() {
    BOOLEAN b = FALSE;
    RTL_OSVERSIONINFOW	osi;
    osi.dwOSVersionInfoSize = sizeof(RTL_OSVERSIONINFOW);
    RtlFillMemory(&osi, sizeof(RTL_OSVERSIONINFOW), 0);
    RtlGetVersion(&osi);
    NtBuildNumber = osi.dwBuildNumber;
    switch (NtBuildNumber) {
        case 7600:
        case 7601:
            ObjectCallbackListOffset = 0xC0;
            b = TRUE;
            break;
        case 9200:
            ObjectCallbackListOffset = 0xC8;
            b = TRUE;
            break;
        case 9600:
            ObjectCallbackListOffset = 0xC8;
            b = TRUE;
            break;
        default:
            if (NtBuildNumber > 10000) {
                ObjectCallbackListOffset = 0xC8;
                b = TRUE;
            }
            break;
    }
    return b;
}
