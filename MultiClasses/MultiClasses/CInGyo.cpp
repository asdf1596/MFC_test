// CInGyo.cpp: 구현 파일
//

#include "pch.h"
#include "MultiClasses.h"
#include "afxdialogex.h"
#include "CInGyo.h"


// CInGyo 대화 상자

IMPLEMENT_DYNAMIC(CInGyo, CDialogEx)

CInGyo::CInGyo(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_GYO_INPUT, pParent)
{

}

CInGyo::~CInGyo()
{
}

void CInGyo::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CInGyo, CDialogEx)
END_MESSAGE_MAP()


// CInGyo 메시지 처리기
