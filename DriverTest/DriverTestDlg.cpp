
// DriverTestDlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "DriverTest.h"
#include "DriverTestDlg.h"
#include "afxdialogex.h"
#include "../HellDriverLib/HellDriver.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

CDriverTestDlg::CDriverTestDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DRIVERTEST_DIALOG, pParent) {
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CDriverTestDlg::DoDataExchange(CDataExchange* pDX) {
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CDriverTestDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CDriverTestDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDC_OPEN_BUTTON, &CDriverTestDlg::OnBnClickedCreatefileButton)
	ON_BN_CLICKED(IDC_READ_BUTTON, &CDriverTestDlg::OnBnClickedReadButton)
	ON_BN_CLICKED(IDC_CLOSE_BUTTON, &CDriverTestDlg::OnBnClickedCloseButton)
	ON_BN_CLICKED(IDC_WRITE_BUTTON, &CDriverTestDlg::OnBnClickedWriteButton)
	ON_BN_CLICKED(IDC_CLOSE_BUTTON2, &CDriverTestDlg::OnBnClickedCloseButton2)
	ON_BN_CLICKED(IDC_CLOSE_BUTTON3, &CDriverTestDlg::OnBnClickedCloseButton3)
	ON_BN_CLICKED(IDC_CLOSE_BUTTON4, &CDriverTestDlg::OnBnClickedCloseButton4)
	ON_BN_CLICKED(IDC_CLOSE_BUTTON5, &CDriverTestDlg::OnBnClickedCloseButton5)
	ON_BN_CLICKED(IDC_CLOSE_BUTTON6, &CDriverTestDlg::OnBnClickedCloseButton6)
	ON_BN_CLICKED(IDC_CLOSE_BUTTON7, &CDriverTestDlg::OnBnClickedCloseButton7)
	ON_BN_CLICKED(IDC_CLOSE_BUTTON9, &CDriverTestDlg::OnBnClickedCloseButton9)
	ON_BN_CLICKED(IDC_CLOSE_BUTTON8, &CDriverTestDlg::OnBnClickedCloseButton8)
	ON_BN_CLICKED(IDC_BUTTON2, &CDriverTestDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CDriverTestDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &CDriverTestDlg::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON5, &CDriverTestDlg::OnBnClickedButton5)
	ON_BN_CLICKED(IDC_BUTTON6, &CDriverTestDlg::OnBnClickedButton6)
END_MESSAGE_MAP()

BOOL CDriverTestDlg::OnInitDialog() {
	CDialogEx::OnInitDialog();
	SetIcon(m_hIcon, TRUE);
	SetIcon(m_hIcon, FALSE);
	return TRUE;
}


void CDriverTestDlg::OnPaint() {
	if (IsIconic()) {
		CPaintDC dc(this);

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		dc.DrawIcon(x, y, m_hIcon);
	} else {
		CDialogEx::OnPaint();
	}
}

HCURSOR CDriverTestDlg::OnQueryDragIcon() {
	return static_cast<HCURSOR>(m_hIcon);
}

void CDriverTestDlg::OnBnClickedOk() {
	CDialogEx::OnOK();
}

static HANDLE DriverHandle = NULL;

void CDriverTestDlg::OnBnClickedCreatefileButton() {
	/*if (DriverHandle == NULL) {
		DriverHandle = CreateFile(HELL_SYMBOL_NAME,
			GENERIC_READ | GENERIC_WRITE,
			FILE_SHARE_READ | FILE_SHARE_WRITE, 
			NULL, 
			OPEN_EXISTING, 
			FILE_ATTRIBUTE_NORMAL, 
			NULL);
		if (DriverHandle == HANDLE(-1)) {
			DriverHandle = NULL;
		}
	}*/

	OpenDriver(HELL_SYMBOL_NAME);

}

void CDriverTestDlg::OnBnClickedCloseButton() {
	CloseDriver();
	/*if (DriverHandle != NULL) {
		if (CloseHandle(DriverHandle)) {
			DriverHandle = NULL;
		}
	}*/
}

void CDriverTestDlg::OnBnClickedWriteButton() {
	char* data = "测试传输!!!";
	char buffer[20] = { 0 };
	LPDWORD outSize = 0;
	DeviceIoControl(DriverHandle, HCODE(0x803), data, (DWORD)strlen(data), &buffer, (DWORD)strlen(buffer), outSize, (LPOVERLAPPED)NULL);
}

void CDriverTestDlg::OnBnClickedReadButton() {
	
}

void CDriverTestDlg::OnBnClickedCloseButton2() {
	StartProtectProcess();
}

void CDriverTestDlg::OnBnClickedCloseButton3() {
	StopProtectProcess();
}

void CDriverTestDlg::OnBnClickedCloseButton4() {
	ProtectProcess(GetCurrentProcessId(), PROCESS_TERMINATE | PROCESS_VM_READ | PROCESS_VM_WRITE);
}


void CDriverTestDlg::OnBnClickedCloseButton5() {
	ProtectProcess(GetCurrentProcessId(), PROCESS_TERMINATE);
}

void CDriverTestDlg::OnBnClickedCloseButton6() {
	UnProtectProcess(GetCurrentProcessId());
}

void CDriverTestDlg::OnBnClickedCloseButton7() {
	int pid = 0;
	CString c;
	GetDlgItem(IDC_EDIT1)->GetWindowTextW(c);
	pid = atoi(CT2A(c.GetBuffer()));
	ProtectProcess(pid, PROCESS_TERMINATE | PROCESS_VM_READ | PROCESS_VM_WRITE);
}

void CDriverTestDlg::OnBnClickedButton2() {
	CString addr;
	GetDlgItem(IDC_EDIT2)->GetWindowTextW(addr);
	UINT64 address = 0l;
	address = wcstoll(addr, NULL, 16);

	int pid = 0;
	CString c;
	GetDlgItem(IDC_EDIT1)->GetWindowTextW(c); //获取
	pid = atoi(CT2A(c.GetBuffer()));
	CString len;
	GetDlgItem(IDC_EDIT3)->GetWindowTextW(len);
	UINT32 length = 0;
	length = atoi(CT2A(len.GetBuffer()));
	UINT32 ml = length + 4;
	CHAR* buffer = (CHAR*)malloc(ml);
	if (buffer == NULL) {
		return;
	}
	memset(buffer, 0, ml);
	//UINT32 rlen = KeProcessMemoryRead(pid, address, buffer, length);
	UINT32 rlen = KeProcessMemoryMDLRead(pid, address, buffer, length);
	CString sss;
	sss.Format(L"%d", rlen);
	MessageBox(sss);
	MessageBoxA(NULL, HTools::w2s((WCHAR*)buffer).c_str(), "123123", 0);
}

void CDriverTestDlg::OnBnClickedButton5() {
	CString addr;
	GetDlgItem(IDC_EDIT2)->GetWindowTextW(addr);
	UINT64 address = 0l;
	address = wcstoll(addr, NULL, 16);

	int pid = 0;
	CString c;
	GetDlgItem(IDC_EDIT1)->GetWindowTextW(c); //获取
	pid = atoi(CT2A(c.GetBuffer()));
	CString len;
	GetDlgItem(IDC_EDIT3)->GetWindowTextW(len);
	UINT32 length = 0;
	length = atoi(CT2A(len.GetBuffer()));
	UINT32 ml = length + 4;
	CHAR* buffer = (CHAR*)malloc(ml);
	if (buffer == NULL) {
		return;
	}
	memset(buffer, 0, ml);
	//UINT32 rlen = KeProcessMemoryRead(pid, address, buffer, length);
	UINT32 rlen = KeProcessMemoryMDLRead(pid, address, buffer, length);
	CString sss;
	sss.Format(L"%d", rlen);
	MessageBox(sss);
	MessageBoxA(NULL, HTools::w2s((WCHAR*)buffer).c_str(), "123123", 0);
}



void CDriverTestDlg::OnBnClickedButton3() {
	CString addr;
	GetDlgItem(IDC_EDIT2)->GetWindowTextW(addr);
	UINT64 address = 0l;
	address = wcstoll(addr, NULL, 16);
	int pid = 0;
	CString process;
	GetDlgItem(IDC_EDIT1)->GetWindowTextW(process);
	pid = atoi(CT2A(process.GetBuffer()));
	CString data;
	GetDlgItem(IDC_EDIT4)->GetWindowTextW(data);
	UINT32 rlen = KeProcessMemoryWrite(pid, address, data.GetBuffer(), data.GetLength() * 2);
	//MessageBox(len);
}

void CDriverTestDlg::OnBnClickedButton4() {
	CString addr;
	GetDlgItem(IDC_EDIT2)->GetWindowTextW(addr);
	UINT64 address = 0l;
	address = wcstoll(addr, NULL, 16);
	int pid = 0;
	CString process;
	GetDlgItem(IDC_EDIT1)->GetWindowTextW(process);
	pid = atoi(CT2A(process.GetBuffer()));
	CString data;
	GetDlgItem(IDC_EDIT4)->GetWindowTextW(data);
	UINT32 rlen = KeProcessOnlyReadMemoryWrite(pid, address, data.GetBuffer(), data.GetLength() * 2);
	//MessageBox(len);
}

void CDriverTestDlg::OnBnClickedButton6() {
	CString addr;
	GetDlgItem(IDC_EDIT2)->GetWindowTextW(addr);
	UINT64 address = 0l;
	address = wcstoll(addr, NULL, 16);
	int pid = 0;
	CString process;
	GetDlgItem(IDC_EDIT1)->GetWindowTextW(process);
	pid = atoi(CT2A(process.GetBuffer()));
	CString data;
	GetDlgItem(IDC_EDIT4)->GetWindowTextW(data);
	UINT32 rlen = KeProcessOnlyReadMemoryCR0Write(pid, address, data.GetBuffer(), data.GetLength() * 2);
}

#define DRIVER_NAME		L"HellDriver"

void CDriverTestDlg::OnBnClickedCloseButton9() {
	TCHAR tcsModulePath[_MAX_PATH];
	::GetModuleFileName(NULL, tcsModulePath, _MAX_PATH);
	
	TCHAR drive[_MAX_DRIVE];
	TCHAR dir[_MAX_DIR];
	_wsplitpath(tcsModulePath, drive, dir, NULL, NULL);

	CString path;
	path.Format(L"%s%sHellDriverLibrary.sys", drive, dir);
	MessageBox(path);
	InstallDriver(DRIVER_NAME, path);
}

void CDriverTestDlg::OnBnClickedCloseButton8() {
	UninstallDriver(DRIVER_NAME);
}










