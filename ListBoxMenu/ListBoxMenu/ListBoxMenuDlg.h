
// ListBoxMenuDlg.h: 헤더 파일
//

#pragma once


// CListBoxMenuDlg 대화 상자
class CListBoxMenuDlg : public CDialogEx
{
// 생성입니다.
public:
	CListBoxMenuDlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_LISTBOXMENU_DIALOG };
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
	afx_msg void OnBnClickedButton1();
	afx_msg void OnLbnSelchangeList2();
	afx_msg void OnLbnSelchangeList3();
	afx_msg void OnLbnSelchangeListDessert();
	afx_msg void OnLbnSelchangeList4();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton5();
//	CListBox m_listMeal;
//	CListBox m_listDessert;
//	CListBox m_listResult;
//	afx_msg void OnClickedButtonMeal();
//	afx_msg void OnClickedButtonDessert();
	CListBox m_listMeal;
//	CListBox m_lsitDessert;
	CListBox m_listResult;
	CListBox m_listDessert;
	afx_msg void OnClickedButtonMeal();
	afx_msg void OnClickedButtonDessert();
//	CString m_strEtc;
	afx_msg void OnClickedButtonEtc();
	CString m_strEtc;
	afx_msg void OnClickedButtonReset();
	afx_msg void OnClickedButtonDel();
};
