// COutAll.cpp: 구현 파일
//

#include "pch.h"
#include "MultiClasses.h"
#include "afxdialogex.h"
#include "COutAll.h"


// COutAll 대화 상자

IMPLEMENT_DYNAMIC(COutAll, CDialogEx)

COutAll::COutAll(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_ALL_OUT, pParent)
	, m_strGyoOut1(_T(""))
	, m_strJunOut1(_T(""))
	, m_strGyoOut2(_T(""))
	, m_strJunOut2(_T(""))
	, m_strJunOut3(_T(""))
{

}

COutAll::~COutAll()
{
}

void COutAll::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_GYO_OUTPUT1, m_strGyoOut1);
	DDX_Text(pDX, IDC_EDIT_JUN_OUTPUT1, m_strJunOut1);
	DDX_Text(pDX, IDC_EDIT_GYO_OUTPUT2, m_strGyoOut2);
	DDX_Text(pDX, IDC_EDIT_JUN_OUTPUT2, m_strJunOut2);
	DDX_Text(pDX, IDC_EDIT_JUN_OUTPUT3, m_strJunOut3);
}


BEGIN_MESSAGE_MAP(COutAll, CDialogEx)
//	ON_COMMAND(ID_APP_EXIT, &COutAll::OnAppExit)
END_MESSAGE_MAP()


// COutAll 메시지 처리기

//void COutAll::OnAppExit()
//{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
//	PostQuitMessage(0);
//}
