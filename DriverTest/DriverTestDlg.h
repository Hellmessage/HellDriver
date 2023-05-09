
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
	afx_msg void OnBnClickedCloseButton2();
	afx_msg void OnBnClickedCloseButton3();
	afx_msg void OnBnClickedCloseButton4();
	afx_msg void OnBnClickedCloseButton5();
	afx_msg void OnBnClickedCloseButton6();
	afx_msg void OnEnChangeEdit1();
	afx_msg void OnBnClickedCloseButton7();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnEnChangeEdit2();
	afx_msg void OnEnChangeEdit3();
	afx_msg void OnBnClickedCloseButton9();
	afx_msg void OnBnClickedCloseButton8();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton4();
	afx_msg void OnBnClickedButton5();
	afx_msg void OnBnClickedButton6();
	afx_msg void OnBnClickedButton7();
	afx_msg void OnBnClickedButton8();
	afx_msg void OnBnClickedCloseButton10();
	afx_msg void OnBnClickedCloseButton11();
	afx_msg void OnBnClickedCloseButton12();
	afx_msg void OnBnClickedCloseButton14();
	afx_msg void OnBnClickedCloseButton13();
	afx_msg void OnBnClickedCloseButton15();
	afx_msg void OnBnClickedCloseButton16();
	afx_msg void OnBnClickedCloseButton17();
};
