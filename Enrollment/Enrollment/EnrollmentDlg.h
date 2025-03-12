
// EnrollmentDlg.h: 헤더 파일
//

#pragma once


// CEnrollmentDlg 대화 상자
class CEnrollmentDlg : public CDialogEx
{
// 생성입니다.
public:
	CEnrollmentDlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ENROLLMENT_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedCheck1();
	afx_msg void OnBnClickedCheck2();
	afx_msg void OnEnChangeEdit3();
	afx_msg void OnEnChangeEdit2();
	afx_msg void OnCbnSelchangeCombo1();
	afx_msg void OnCbnSelchangeCombo2();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButtonName();
	CString m_strName;
	CString m_strNum;
	CString m_strCell;
	BOOL m_chA;
	BOOL m_chB;
	CComboBox m_cbPoint1;
	CComboBox m_cbPoint2;
	CButton m_rOnline;
	CListCtrl m_listView;
	int m_nSelected;
	void Init();
	afx_msg void OnClickedButtonInput();
	afx_msg void OnClickedButtonDel();
	afx_msg void OnClickedButtonInit();
	afx_msg void OnClickedButtonExit();
};
