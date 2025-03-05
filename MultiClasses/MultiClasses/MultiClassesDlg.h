
// MultiClassesDlg.h: 헤더 파일
//

#pragma once
#include "CInJun.h"
#include "CInGyo.h"
#include "COutAll.h"

// CMultiClassesDlg 대화 상자
class CMultiClassesDlg : public CDialogEx
{
// 생성입니다.
public:
	CMultiClassesDlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.

	CInJun m_InJunDlg;
	CInGyo m_InGyoDlg;
	COutAll m_OutAllDlg;

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MULTICLASSES_DIALOG };
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
	afx_msg void OnClickedButtonJunInput();
	afx_msg void OnClickedButtonGyoInput();
	afx_msg void OnClickedButtonAllOutput();
	afx_msg void OnClickedButtonExit();
};
