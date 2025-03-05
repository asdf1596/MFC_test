// CInName.cpp: 구현 파일
//

#include "pch.h"
#include "ClassAdd2.h"
#include "afxdialogex.h"
#include "CInName.h"


// CInName 대화 상자

IMPLEMENT_DYNAMIC(CInName, CDialogEx)

CInName::CInName(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_IN_NAME, pParent)
	, m_strEngName(_T(""))
	, m_strInKorName(_T(""))
{

}

CInName::~CInName()
{
}

void CInName::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_IN_ENG_NAME, m_strEngName);
	DDX_Text(pDX, IDC_EDIT_IN_KOR_NAME, m_strInKorName);
}


BEGIN_MESSAGE_MAP(CInName, CDialogEx)
END_MESSAGE_MAP()


// CInName 메시지 처리기
