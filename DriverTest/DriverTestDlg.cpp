
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
		DriverHandle = CreateFile(符号连接名,
			GENERIC_READ | GENERIC_WRITE,
			FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	}
}

void CDriverTestDlg::OnBnClickedCloseButton() {
	if (DriverHandle != NULL) {
		CloseHandle(DriverHandle);
	}
}

void CDriverTestDlg::OnBnClickedWriteButton() {
	char* data = "测试传输!!!";
	char buffer[20] = { 0 };
	LPDWORD outSize = 0;
	DeviceIoControl(DriverHandle, HCODE(0x803), data, (DWORD)strlen(data), &buffer, 20, outSize, (LPOVERLAPPED)NULL);
}

void CDriverTestDlg::OnBnClickedReadButton() {
	
}


