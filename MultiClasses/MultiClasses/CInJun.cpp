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
{

}

CInJun::~CInJun()
{
}

void CInJun::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CInJun, CDialogEx)
END_MESSAGE_MAP()


// CInJun 메시지 처리기
