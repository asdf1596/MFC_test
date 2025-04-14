
// RGBSliderDlg.h: 헤더 파일
//

#pragma once


// CRGBSliderDlg 대화 상자
class CRGBSliderDlg : public CDialogEx
{
// 생성입니다.
public:
	CRGBSliderDlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_RGBSLIDER_DIALOG };
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
	CSliderCtrl m_sldR;
	CSliderCtrl m_sldG;
	CSliderCtrl m_sldB;
	int m_nR;
	int m_nG;
	int m_nB;
	COLORREF m_cRGB;
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	void Clear();
	afx_msg void OnClickedButtonClear();
	afx_msg void OnClickedButtonExit();
	afx_msg void OnStnClickedStaticRgb();
};
