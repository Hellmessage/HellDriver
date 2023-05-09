#ifndef __HELL_HEADER__
#define __HELL_HEADER__

#include "framework.h"
#include "../Hell Driver Library/Common.h"
#include <iostream>
#include <strsafe.h>

#define HELLCALL __declspec(dllexport)

#define HLog(format, ...)           HDebugLog(L"Hell: "##format"\n", ##__VA_ARGS__)


static void HDebugLog(LPCTSTR format, ...) {
	va_list args;
	va_start(args, format);
	TCHAR buf[1024] = { 0 };
	StringCchVPrintf(buf, 1023, format, args);
	va_end(args);
	buf[1023] = L'\0';
	OutputDebugString(buf);
	wprintf(buf);
}

#endif // !__HELL_HEADER__
