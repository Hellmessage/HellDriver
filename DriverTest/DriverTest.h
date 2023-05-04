
// DriverTest.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CDriverTestApp:
// See DriverTest.cpp for the implementation of this class
//

class CDriverTestApp : public CWinApp
{
public:
	CDriverTestApp();

// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CDriverTestApp theApp;
