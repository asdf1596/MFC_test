#pragma once
#include "afxdialogex.h"


// CInName 대화 상자

class CInName : public CDialogEx
{
	DECLARE_DYNAMIC(CInName)

public:
	CInName(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CInName();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_IN_NAME };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	CString m_strEngName;
	CString m_strInKorName;
};
