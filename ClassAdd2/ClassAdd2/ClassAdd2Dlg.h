
// ClassAdd2Dlg.h: 헤더 파일
//

#pragma once
#include "CInName.h"
#include "CInContact.h"
#include "COutAll.h"

// CClassAdd2Dlg 대화 상자
class CClassAdd2Dlg : public CDialogEx
{
// 생성입니다.
public:
	CClassAdd2Dlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.

	CInName m_InNameDlg;
	CInContact m_InContactDlg;
	COutAll m_OutAllDlg;

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CLASSADD2_DIALOG };
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
	afx_msg void OnClickedButtonNameIn();
	afx_msg void OnClickedButtonContactIn();
	afx_msg void OnClickedButtonNameOut();
	afx_msg void OnClickedButtonAllOut();
	afx_msg void OnClickedButtonExit();
};
