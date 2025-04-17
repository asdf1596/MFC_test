
// TAB_AREADlg.h: 헤더 파일
//

#pragma once


// CTABAREADlg 대화 상자
class CTABAREADlg : public CDialogEx
{
// 생성입니다.
public:
	CTABAREADlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_TAB_AREA_DIALOG };
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
//	double m_dTribResult;
	CTabCtrl m_tabArea;
	double m_dCirR;
	double m_dCirResult;
//	double m_dTribA;
//	double m_dTribB;
	double m_dRectA;
	double m_dRectB;
	double m_dRectResult;
	afx_msg void OnSelchangeTabArea(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnClickedButtonCir();
	afx_msg void OnClickedButtonRect();
	afx_msg void OnClickedButtonTri();
	double m_dTriResult;
	double m_dTriB;
	double m_dTriA;
	afx_msg void OnClickedButtonShow();
	afx_msg void OnClickedButtonExit();
};
