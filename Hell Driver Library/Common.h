#ifndef __HELL_COMMON_HEADER__
#define __HELL_COMMON_HEADER__

#define 驱动设备名                       L"\\DEVICE\\HellDriver"
#define 符号连接名                       L"\\??\\HellDriver"

#ifdef HELL_DRIVER
#include <ntifs.h>
#else
#include <Windows.h>
#include <winioctl.h>
#endif // HELL_DRIVER

#define HCODE(code)                     CTL_CODE(FILE_DEVICE_UNKNOWN, code, METHOD_BUFFERED, FILE_ANY_ACCESS)

#endif // !__HELL_COMMON_HEADER__