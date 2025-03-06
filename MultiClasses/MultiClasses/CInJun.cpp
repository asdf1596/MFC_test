// CInJun.cpp: 구현 파일
//

#include "pch.h"
#include "MultiClasses.h"
#include "afxdialogex.h"
#include "CInJun.h"


// CInJun 대화 상자

IMPLEMENT_DYNAMIC(CInJun, CDialogEx)

CInJun::CInJun(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_JUN_INPUT, pParent)
	, m_strJunIn1(_T(""))
	, m_strJunIn2(_T(""))
	, m_strJunIn3(_T(""))
{

}

CInJun::~CInJun()
{
}

void CInJun::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_JUN_INPUT1, m_strJunIn1);
	DDX_Text(pDX, IDC_EDIT_JUN_INPUT2, m_strJunIn2);
	DDX_Text(pDX, IDC_EDIT_JUN_INPUT3, m_strJunIn3);
}


BEGIN_MESSAGE_MAP(CInJun, CDialogEx)
END_MESSAGE_MAP()


// CInJun 메시지 처리기
