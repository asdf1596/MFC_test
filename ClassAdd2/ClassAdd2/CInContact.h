#pragma once
#include "afxdialogex.h"


// CInContact 대화 상자

class CInContact : public CDialogEx
{
	DECLARE_DYNAMIC(CInContact)

public:
	CInContact(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CInContact();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_IN_CONTACT };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	CString m_strInCell;
	CString m_strInEmaill;
};
