
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
	ON_BN_CLICKED(IDC_BUTTON7, &CDriverTestDlg::OnBnClickedButton7)
	ON_BN_CLICKED(IDC_BUTTON8, &CDriverTestDlg::OnBnClickedButton8)
	ON_BN_CLICKED(IDC_CLOSE_BUTTON10, &CDriverTestDlg::OnBnClickedCloseButton10)
	ON_BN_CLICKED(IDC_CLOSE_BUTTON11, &CDriverTestDlg::OnBnClickedCloseButton11)
	ON_BN_CLICKED(IDC_CLOSE_BUTTON12, &CDriverTestDlg::OnBnClickedCloseButton12)
	ON_BN_CLICKED(IDC_CLOSE_BUTTON14, &CDriverTestDlg::OnBnClickedCloseButton14)
	ON_BN_CLICKED(IDC_CLOSE_BUTTON13, &CDriverTestDlg::OnBnClickedCloseButton13)
	ON_BN_CLICKED(IDC_CLOSE_BUTTON15, &CDriverTestDlg::OnBnClickedCloseButton15)
	ON_BN_CLICKED(IDC_CLOSE_BUTTON16, &CDriverTestDlg::OnBnClickedCloseButton16)
	ON_BN_CLICKED(IDC_CLOSE_BUTTON17, &CDriverTestDlg::OnBnClickedCloseButton17)
END_MESSAGE_MAP()

BOOL CDriverTestDlg::OnInitDialog() {
	CDialogEx::OnInitDialog();
	SetIcon(m_hIcon, TRUE);
	SetIcon(m_hIcon, FALSE);

	CString str;
	str.Format(L"%d", GetCurrentProcessId());
	GetDlgItem(IDC_EDIT5)->SetWindowTextW(str);

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
	OpenDriver(HELL_SYMBOL_NAME);
}

void CDriverTestDlg::OnBnClickedCloseButton() {
	CloseDriver();
}

void CDriverTestDlg::OnBnClickedWriteButton() {
	
}

void CDriverTestDlg::OnBnClickedReadButton() {
	UINT32 at = HPAT_ENHANCE | HPAT_REDUCE | HPAT_PROTECT;
	CString str;
	str.Format(L"%d", at);
	MessageBox(str);

	UINT et = (at & HPAT_ENHANCE) == HPAT_ENHANCE;
	str.Format(L"%d", et);
	MessageBox(str);

	UINT rt = (at & HPAT_REDUCE) == HPAT_REDUCE;
	str.Format(L"%d", rt);
	MessageBox(str);

	UINT pt = (at & HPAT_PROTECT) == HPAT_PROTECT;
	str.Format(L"%d", pt);
	MessageBox(str);

}


void CDriverTestDlg::OnBnClickedCloseButton4() {
}

void CDriverTestDlg::OnBnClickedCloseButton5() {
}

void CDriverTestDlg::OnBnClickedCloseButton6() {
}

void CDriverTestDlg::OnBnClickedCloseButton7() {
}

void CDriverTestDlg::OnBnClickedCloseButton11() {
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
	UINT32 rlen = KeProcessMemoryCR3Read(pid, address, buffer, length);
	CString sss;
	sss.Format(L"%d", rlen);
	MessageBox(sss);
	MessageBoxA(NULL, HTools::w2s((WCHAR*)buffer).c_str(), "123123", 0);
}

void CDriverTestDlg::OnBnClickedButton7() {
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
	UINT32 rlen = KeProcessPhysicalMemoryRead(pid, address, buffer, length);
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


void CDriverTestDlg::OnBnClickedButton8() {
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
	UINT32 rlen = KeProcessPhysicalMemoryWrite(pid, address, data.GetBuffer(), data.GetLength() * 2);
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



void CDriverTestDlg::OnBnClickedCloseButton10() {
	GetFetchHook();
}
















void CDriverTestDlg::OnBnClickedCloseButton2() {
	ProcessAccessInstall();
}

void CDriverTestDlg::OnBnClickedCloseButton3() {
	ProcessAccessUninstall();
}

//提升
void CDriverTestDlg::OnBnClickedCloseButton12() {
	int pid = 0;
	CString tpid;
	GetDlgItem(IDC_EDIT5)->GetWindowTextW(tpid);
	pid = atoi(CT2A(tpid.GetBuffer()));

	ProcessAccessHookSet(pid, HPAT_ENHANCE, PROCESS_VM_READ | PROCESS_VM_WRITE | PROCESS_TERMINATE);
}

//维持
void CDriverTestDlg::OnBnClickedCloseButton14() {
	int pid = 0;
	CString tpid;
	GetDlgItem(IDC_EDIT5)->GetWindowTextW(tpid);
	pid = atoi(CT2A(tpid.GetBuffer()));

	ProcessAccessHookSet(pid, HPAT_MAINTAIN, 0);
}

//降低
void CDriverTestDlg::OnBnClickedCloseButton13() {
	int pid = 0;
	CString tpid;
	GetDlgItem(IDC_EDIT5)->GetWindowTextW(tpid);
	pid = atoi(CT2A(tpid.GetBuffer()));

	ProcessAccessHookSet(pid, HPAT_REDUCE, PROCESS_VM_READ | PROCESS_VM_WRITE | PROCESS_TERMINATE);
}

//保护读写关
void CDriverTestDlg::OnBnClickedCloseButton15() {
	int pid = 0;
	CString tpid;
	GetDlgItem(IDC_EDIT5)->GetWindowTextW(tpid);
	pid = atoi(CT2A(tpid.GetBuffer()));

	ProcessAccessHookSet(pid, HPAT_PROTECT, PROCESS_VM_READ | PROCESS_VM_WRITE | PROCESS_TERMINATE);
}

//移除
void CDriverTestDlg::OnBnClickedCloseButton16() {
	int pid = 0;
	CString tpid;
	GetDlgItem(IDC_EDIT5)->GetWindowTextW(tpid);
	pid = atoi(CT2A(tpid.GetBuffer()));

	ProcessAccessHookDel(pid);
}




















void HellSystemHandleEvent(UNICODE_STRING type, UNICODE_STRING name, SYSTEM_HANDLE_TABLE_ENTRY_INFO info, HANDLE handle) {
	if (_wcsicmp(type.Buffer, L"Process") == 0) {
		DWORD tpid = HandleToProcessId(handle);
		DWORD cpid = info.ProcessId;
		if (tpid == 3908 || cpid == 3908) {
			MessageBoxA(NULL, "123123", "1", 0);
		}
		HLog("%wZ    %wZ    %lx    %d      %d", type, name, handle, info.ProcessId, HandleToProcessId(handle));
	}
}


void CDriverTestDlg::OnBnClickedCloseButton17() {
	EnumProcessHandle(HellSystemHandleEvent);
	// TODO: Add your control notification handler code here
}