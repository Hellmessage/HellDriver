
// DriverTestDlg.h : header file
//

#pragma once


// CDriverTestDlg dialog
class CDriverTestDlg : public CDialogEx
{
// Construction
public:
	CDriverTestDlg(CWnd* pParent = nullptr);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DRIVERTEST_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCreatefileButton();
	afx_msg void OnBnClickedReadButton();
	afx_msg void OnBnClickedCloseButton();
	afx_msg void OnBnClickedWriteButton();
};
