
// WinProExeDlg.h: 헤더 파일
//

#pragma once


// CWinProExeDlg 대화 상자
class CWinProExeDlg : public CDialogEx
{
// 생성입니다.
public:
	CWinProExeDlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_WINPROEXE_DIALOG };
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
	afx_msg void OnBnClickedButton2();
	BOOL m_chActive;
	BOOL m_chShow;
	CString m_strInput;
	void ActiveShow();
	afx_msg void OnClickedCheckActive();
	afx_msg void OnClickedCheckShow();
	afx_msg void OnClickedButtonClear();
	afx_msg void OnClickedButtonExit();
	afx_msg void OnChangeEditInput();
};
