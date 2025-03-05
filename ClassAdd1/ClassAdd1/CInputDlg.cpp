// CInputDlg.cpp: 구현 파일
//

#include "pch.h"
#include "ClassAdd1.h"
#include "afxdialogex.h"
#include "CInputDlg.h"


// CInputDlg 대화 상자

IMPLEMENT_DYNAMIC(CInputDlg, CDialogEx)

CInputDlg::CInputDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_INPUT, pParent)
	, m_strInName(_T(""))
	, m_strInNum(_T(""))
{

}

CInputDlg::~CInputDlg()
{
}

void CInputDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_IN_NAME, m_strInName);
	DDX_Text(pDX, IDC_EDIT_IN_NUM, m_strInNum);
}


BEGIN_MESSAGE_MAP(CInputDlg, CDialogEx)
END_MESSAGE_MAP()


// CInputDlg 메시지 처리기
