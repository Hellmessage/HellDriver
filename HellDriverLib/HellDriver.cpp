#include "HellDriver.h"

HANDLE g_Driver = NULL;

int InstallDriver(LPCTSTR name, LPCTSTR path) {
	SC_HANDLE manage = NULL;
	SC_HANDLE server = NULL;
	manage = OpenSCManager(NULL, NULL, SC_MANAGER_ALL_ACCESS);
	if(manage == NULL) {
		return -1;
	}
	server = CreateService(manage,
		name, name,
		SERVICE_ALL_ACCESS,
		SERVICE_FILE_SYSTEM_DRIVER,
		SERVICE_AUTO_START,
		SERVICE_ERROR_NORMAL,
		path,
		NULL, NULL, NULL, NULL, NULL);
	if (server == NULL) {
		CloseServiceHandle(manage);
		DWORD result = GetLastError();
		if (result != ERROR_IO_PENDING && result != ERROR_SERVICE_EXISTS) {
			return -2;
		}
		return 1;
	}
	CloseServiceHandle(manage);
	CloseServiceHandle(server);
	return 1;
}

void UninstallDriver(LPCTSTR name) {
	SC_HANDLE manage = NULL;
	SC_HANDLE server = NULL;
	BOOL result = FALSE;
	SERVICE_STATUS status = { 0 };
	manage = OpenSCManager(NULL, NULL, SC_MANAGER_ALL_ACCESS);
	if (manage == NULL) {
		return;
	}
	server = OpenService(manage, name, SERVICE_ALL_ACCESS);
	if (server == NULL) {
		CloseServiceHandle(manage);
		return;
	}
	result = ControlService(server, SERVICE_CONTROL_STOP, &status);
	result = DeleteService(server);
	CloseServiceHandle(manage);
	CloseServiceHandle(server);
}

void OpenDriver(LPCTSTR symbol) {
	if (g_Driver == NULL) {
		g_Driver = CreateFile(symbol,
			GENERIC_READ | GENERIC_WRITE,
			FILE_SHARE_READ | FILE_SHARE_WRITE,
			NULL,
			OPEN_EXISTING,
			FILE_ATTRIBUTE_NORMAL,
			NULL);
		if (g_Driver == HANDLE(-1)) {
			g_Driver = NULL;
		}
	}
}

void CloseDriver() {
	if (g_Driver != NULL) {
		if (CloseHandle(g_Driver)) {
			g_Driver = NULL;
		}
	}
}

HANDLE GetDriver() {
	return g_Driver;
}
