
// DriverTestDlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "DriverTest.h"
#include "DriverTestDlg.h"
#include "afxdialogex.h"

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
END_MESSAGE_MAP()

BOOL CDriverTestDlg::OnInitDialog() {
	CDialogEx::OnInitDialog();
	SetIcon(m_hIcon, TRUE);
	SetIcon(m_hIcon, FALSE);

	// TODO: Add extra initialization here

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
	if (DriverHandle == NULL) {
		DriverHandle = CreateFile(HELL_SYMBOL_NAME,
			GENERIC_READ | GENERIC_WRITE,
			FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
		if (DriverHandle == HANDLE(-1)) {
			DriverHandle = NULL;
		}
	}
}

void CDriverTestDlg::OnBnClickedCloseButton() {
	if (DriverHandle != NULL) {
		if (CloseHandle(DriverHandle)) {
			DriverHandle = NULL;
		}
	}
}

void CDriverTestDlg::OnBnClickedWriteButton() {
	char* data = "²âÊÔ´«Êä!!!";
	char buffer[20] = { 0 };
	LPDWORD outSize = 0;
	DeviceIoControl(DriverHandle, HCODE(0x803), data, (DWORD)strlen(data), &buffer, (DWORD)strlen(buffer), outSize, (LPOVERLAPPED)NULL);
}

void CDriverTestDlg::OnBnClickedReadButton() {
	
}

void CDriverTestDlg::OnBnClickedCloseButton2() {
	LPDWORD outSize = 0;
	DeviceIoControl(DriverHandle, CODE_LOAD_SSDTHOOK, NULL, 0, NULL, 0, outSize, (LPOVERLAPPED)NULL);
}

void CDriverTestDlg::OnBnClickedCloseButton3() {
	LPDWORD outSize = 0;
	DeviceIoControl(DriverHandle, CODE_UNLOAD_SSDTHOOK, NULL, 0, NULL, 0, outSize, (LPOVERLAPPED)NULL);
}


void CDriverTestDlg::OnBnClickedCloseButton4() {
	PProtectProcessItem item = (PProtectProcessItem)malloc(sizeof(ProtectProcessItem));
	if (item != NULL) {
		item->ProcessId = GetCurrentProcessId();
		item->ExcludeAccess = PROCESS_TERMINATE | PROCESS_VM_READ | PROCESS_VM_WRITE;
		LPDWORD outSize = 0;
		DeviceIoControl(DriverHandle, CODE_IN_SSDT_PROTECT, item, sizeof(ProtectProcessItem), NULL, 0, outSize, (LPOVERLAPPED)NULL);
		free(item);
	}
}


void CDriverTestDlg::OnBnClickedCloseButton5() {
	PProtectProcessItem item = (PProtectProcessItem)malloc(sizeof(ProtectProcessItem));
	if (item != NULL) {
		item->ProcessId = GetCurrentProcessId();
		item->ExcludeAccess = PROCESS_TERMINATE;
		LPDWORD outSize = 0;
		DeviceIoControl(DriverHandle, CODE_IN_SSDT_PROTECT, item, sizeof(ProtectProcessItem), NULL, 0, outSize, (LPOVERLAPPED)NULL);
		free(item);
	}
}


void CDriverTestDlg::OnBnClickedCloseButton6() {
	PProtectProcessItem item = (PProtectProcessItem)malloc(sizeof(ProtectProcessItem));
	if (item != NULL) {
		item->ProcessId = GetCurrentProcessId();
		item->ExcludeAccess = 0;
		LPDWORD outSize = 0;
		DeviceIoControl(DriverHandle, CODE_UN_SSDT_PROTECT, item, sizeof(ProtectProcessItem), NULL, 0, outSize, (LPOVERLAPPED)NULL);
		free(item);
	}
}
