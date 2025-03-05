// CInContact.cpp: 구현 파일
//

#include "pch.h"
#include "ClassAdd2.h"
#include "afxdialogex.h"
#include "CInContact.h"


// CInContact 대화 상자

IMPLEMENT_DYNAMIC(CInContact, CDialogEx)

CInContact::CInContact(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_IN_CONTACT, pParent)
	, m_strInCell(_T(""))
	, m_strInEmaill(_T(""))
{

}

CInContact::~CInContact()
{
}

void CInContact::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_IN_CELL, m_strInCell);
	DDX_Text(pDX, IDC_EDIT_IN_EMAIL, m_strInEmaill);
}


BEGIN_MESSAGE_MAP(CInContact, CDialogEx)
END_MESSAGE_MAP()


// CInContact 메시지 처리기
