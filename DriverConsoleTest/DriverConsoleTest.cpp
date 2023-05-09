// DriverConsoleTest.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

#include "../HellDriverLib/HellDriver.h"


void HellSystemHandleEvent(UNICODE_STRING type, UNICODE_STRING name, SYSTEM_HANDLE_TABLE_ENTRY_INFO info, HANDLE handle) {
	if (_wcsicmp(type.Buffer, L"Process") == 0) {
		//DWORD tpid = HandleToProcessId(handle);
		//DWORD cpid = info.ProcessId;
		//if (tpid == 3908 || cpid == 3908) {
		//	MessageBoxA(NULL, "123123", "1", 0);
		//}
		HLog("%wZ    %wZ    %lx    %d      %d", type, name, handle, info.ProcessId, HandleToProcessId(handle));
	}
}

int main() {
	setlocale(LC_CTYPE, "");
	EnumProcessHandle(HellSystemHandleEvent);
	return 0;
}