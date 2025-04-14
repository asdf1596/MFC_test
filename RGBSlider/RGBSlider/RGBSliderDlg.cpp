
// RGBSliderDlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "RGBSlider.h"
#include "RGBSliderDlg.h"
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


// CRGBSliderDlg 대화 상자



CRGBSliderDlg::CRGBSliderDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_RGBSLIDER_DIALOG, pParent)
	, m_nR(0)
	, m_nG(0)
	, m_nB(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CRGBSliderDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_SLIDER_R, m_sldR);
	DDX_Control(pDX, IDC_SLIDER_G, m_sldG);
	DDX_Control(pDX, IDC_SLIDER_B, m_sldB);
	DDX_Text(pDX, IDC_EDIT_R, m_nR);
	DDX_Text(pDX, IDC_EDIT_G, m_nG);
	DDX_Text(pDX, IDC_EDIT_B, m_nB);
}

BEGIN_MESSAGE_MAP(CRGBSliderDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_HSCROLL()
	ON_BN_CLICKED(IDC_BUTTON_CLEAR, &CRGBSliderDlg::OnClickedButtonClear)
	ON_BN_CLICKED(IDC_BUTTON_EXIT, &CRGBSliderDlg::OnClickedButtonExit)
END_MESSAGE_MAP()


// CRGBSliderDlg 메시지 처리기

BOOL CRGBSliderDlg::OnInitDialog()
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

	m_sldR.SetRange(0, 255);
	m_sldB.SetRange(0, 255);
	m_sldG.SetRange(0, 255);

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CRGBSliderDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CRGBSliderDlg::OnPaint()
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

		CRect rect;
		CClientDC rgbdc(GetDlgItem(IDC_STATIC_RGB));
		CStatic *pSRGB = (CStatic *)GetDlgItem(IDC_STATIC_RGB);
		pSRGB->GetClientRect(&rect);
		rgbdc.FillSolidRect(rect, m_cRGB);
		pSRGB->InvalidateRect(rect, TRUE);
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CRGBSliderDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}











//미완



















void CRGBSliderDlg::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	CRect rect;
	GetDlgItem(IDC_STATIC_RGB)->GetWindowRect(&rect);
	ScreenToClient(&rect);
	int nR = m_sldR.GetPos();
	int nG = m_sldG.GetPos();
	int nB = m_sldB.GetPos();

	if ((pScrollBar == (CScrollBar*)&m_sldR) || (pScrollBar == (CScrollBar*)&m_sldG) || (pScrollBar == (CScrollBar*)&m_sldB))
	{
		int nPosR = m_sldR.GetPos();
		int nPosG = m_sldG.GetPos();
		int nPosB = m_sldB.GetPos();

		m_nR = nPosR;
		m_nG = nPosG;
		m_nB = nPosB;

		m_cRGB = RGB(m_nR, m_nG, m_nB);
		UpdateData(FALSE);
		InvalidateRect(&rect);
	}
	else {

		CDialogEx::OnHScroll(nSBCode, nPos, pScrollBar);
	}
}

void CRGBSliderDlg::Clear()
{
	// TODO: 여기에 구현 코드 추가.
	UpdateData(TRUE);

	CRect rect;
	GetDlgItem(IDC_STATIC_RGB)->GetWindowRect(&rect);
	ScreenToClient(&rect);
	InvalidateRect(&rect);

	m_cRGB = RGB(0, 0, 0);

	m_sldR.SetPos(0);
	m_sldG.SetPos(0);
	m_sldB.SetPos(0);

	m_nB = 0;
	m_nG = 0;
	m_nR = 0;

	m_cRGB = RGB(0, 0, 0);
	UpdateData(FALSE);
}

void CRGBSliderDlg::OnClickedButtonClear()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	Clear();
}

void CRGBSliderDlg::OnClickedButtonExit()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	OnOK();
}
