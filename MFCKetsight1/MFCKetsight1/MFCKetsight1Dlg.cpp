﻿
// MFCKetsight1Dlg.cpp: 구현 파일
//

#include "visa.h"
#include "pch.h"
#include "framework.h"
#include "MFCKetsight1.h"
#include "MFCKetsight1Dlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

// 구현입니다.
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CMFCKetsight1Dlg 대화 상자



CMFCKetsight1Dlg::CMFCKetsight1Dlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFCKETSIGHT1_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCKetsight1Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMFCKetsight1Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_SCAN, &CMFCKetsight1Dlg::OnClickedButtonScan)
END_MESSAGE_MAP()


// CMFCKetsight1Dlg 메시지 처리기

BOOL CMFCKetsight1Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CMFCKetsight1Dlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 애플리케이션의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CMFCKetsight1Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CMFCKetsight1Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CMFCKetsight1Dlg::OnClickedButtonScan()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	m_comboDevice.ResetContent();  // 기존 목록 비우기

	ViSession rm;
	ViFindList findList;
	ViChar instrDesc[VI_FIND_BUFLEN];
	ViUInt32 numInstrs;
	ViStatus status;

	if (viOpenDefaultRM(&rm) != VI_SUCCESS) {
		AfxMessageBox(_T("VISA 리소스 매니저 열기 실패"));
		return;
	}

	status = viFindRsrc(rm, "?*INSTR", &findList, &numInstrs, instrDesc);
	if (status != VI_SUCCESS || numInstrs == 0) {
		AfxMessageBox(_T("VISA 장비 없음"));
		viClose(rm);
		return;
	}

	for (ViUInt32 i = 0; i < numInstrs; ++i) {
		ViSession instr;
		status = viOpen(rm, instrDesc, VI_NULL, VI_NULL, &instr);
		CString displayStr(instrDesc);  // 기본 리소스 문자열

		if (status == VI_SUCCESS) {
			const char* cmd = "*IDN?\n";
			viWrite(instr, (ViBuf)cmd, (ViUInt32)strlen(cmd), VI_NULL);

			char idnResponse[256] = { 0 };
			viRead(instr, (ViBuf)idnResponse, sizeof(idnResponse), VI_NULL);

			// 장비 유형 판별
			if (strstr(idnResponse, "344") != nullptr)
				displayStr += _T(" (DMM)");
			else if (strstr(idnResponse, "E363") != nullptr)
				displayStr += _T(" (Power Supply)");

			viClose(instr);
		}
		else {
			displayStr += _T(" (연결 실패)");
		}

		m_comboDevice.AddString(displayStr);

		if (i + 1 < numInstrs)
			viFindNext(findList, instrDesc);
	}

	viClose(findList);
	viClose(rm);
}
