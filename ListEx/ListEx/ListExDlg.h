
// ListExDlg.h: 헤더 파일
//

#pragma once


// CListExDlg 대화 상자
class CListExDlg : public CDialogEx
{
// 생성입니다.
public:
	CListExDlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_LISTEX_DIALOG };
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
	afx_msg void OnBnClickedButton3();
	afx_msg void OnLbnSelchangeList1();
	afx_msg void OnLbnSelchangeList2();
	afx_msg void OnLbnSelchangeListLang();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButtonDel();
	CListBox m_listGyo;
	CListBox m_listLang;
	CListBox m_listGong;
	CListBox m_listChoose;
	afx_msg void OnClickedButtonGyo();
	afx_msg void OnClickedButtonLang();
	afx_msg void OnClickedButtonGong();
	afx_msg void OnClickedButtonChoose();
	CListBox m_listFinal;
	afx_msg void OnClickedButtonDel();
};
