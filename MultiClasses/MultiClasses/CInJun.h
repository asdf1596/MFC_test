#pragma once
#include "afxdialogex.h"


// CInJun 대화 상자

class CInJun : public CDialogEx
{
	DECLARE_DYNAMIC(CInJun)

public:
	CInJun(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CInJun();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_JUN_INPUT };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
};
