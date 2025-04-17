
// TAB_AREADlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "TAB_AREA.h"
#include "TAB_AREADlg.h"
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


// CTABAREADlg 대화 상자



CTABAREADlg::CTABAREADlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_TAB_AREA_DIALOG, pParent)
	, m_dCirR(0)
	, m_dCirResult(0)
	, m_dRectA(0)
	, m_dRectB(0)
	, m_dRectResult(0)
	, m_dTriResult(0)
	, m_dTriB(0)
	, m_dTriA(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CTABAREADlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	//  DDX_Text(pDX, IDC_EDIT_TRI_RESULT, m_dTribResult);
	DDX_Control(pDX, IDC_TAB_AREA, m_tabArea);
	DDX_Text(pDX, IDC_EDIT_CIR_R, m_dCirR);
	DDX_Text(pDX, IDC_EDIT_CIR_RESULT, m_dCirResult);
	//  DDX_Text(pDX, IDC_EDIT_TRI_A, m_dTribA);
	//  DDX_Text(pDX, IDC_EDIT_TRI_B, m_dTribB);
	DDX_Text(pDX, IDC_EDIT_RECT_A, m_dRectA);
	DDX_Text(pDX, IDC_EDIT_RECT_B, m_dRectB);
	DDX_Text(pDX, IDC_EDIT_RECT_RESULT, m_dRectResult);
	DDX_Text(pDX, IDC_EDIT_TRI_RESULT, m_dTriResult);
	DDX_Text(pDX, IDC_EDIT_TRI_B, m_dTriB);
	DDX_Text(pDX, IDC_EDIT_TRI_A, m_dTriA);
}

BEGIN_MESSAGE_MAP(CTABAREADlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB_AREA, &CTABAREADlg::OnSelchangeTabArea)
	ON_BN_CLICKED(IDC_BUTTON_CIR, &CTABAREADlg::OnClickedButtonCir)
	ON_BN_CLICKED(IDC_BUTTON_RECT, &CTABAREADlg::OnClickedButtonRect)
	ON_BN_CLICKED(IDC_BUTTON_TRI, &CTABAREADlg::OnClickedButtonTri)
	ON_BN_CLICKED(IDC_BUTTON_SHOW, &CTABAREADlg::OnClickedButtonShow)
	ON_BN_CLICKED(IDC_BUTTON_EXIT, &CTABAREADlg::OnClickedButtonExit)
END_MESSAGE_MAP()


// CTABAREADlg 메시지 처리기

BOOL CTABAREADlg::OnInitDialog()
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

	TC_ITEM tabItem;
	LPSTR tabName[3] = { _T("삼각형"), _T("원"), _T("사각형") };
	for (int nIndex = 0; nIndex < 3; nIndex++) {
		tabItem.mask = TCIF_TEXT;
		tabItem.pszText = tabName[nIndex];
		m_tabArea.InsertItem(nIndex, &tabItem);
	}
	GetDlgItem(IDC_STATIC_TRI)->ShowWindow(TRUE);
	GetDlgItem(IDC_STATIC_TRI_A)->ShowWindow(TRUE);
	GetDlgItem(IDC_STATIC_TRI_B)->ShowWindow(TRUE);
	GetDlgItem(IDC_STATIC_TRI_RESULT)->ShowWindow(TRUE);
	GetDlgItem(IDC_BUTTON_TRI)->ShowWindow(TRUE);
	GetDlgItem(IDC_EDIT_TRI_A)->ShowWindow(TRUE);
	GetDlgItem(IDC_EDIT_TRI_B)->ShowWindow(TRUE);
	GetDlgItem(IDC_EDIT_TRI_RESULT)->ShowWindow(TRUE);

	GetDlgItem(IDC_STATIC_CIR)->ShowWindow(FALSE);
	GetDlgItem(IDC_STATIC_CIR_R)->ShowWindow(FALSE);
	GetDlgItem(IDC_STATIC_CIR_RESULT)->ShowWindow(FALSE);
	GetDlgItem(IDC_BUTTON_CIR)->ShowWindow(FALSE);
	GetDlgItem(IDC_EDIT_CIR_R)->ShowWindow(FALSE);
	GetDlgItem(IDC_EDIT_CIR_RESULT)->ShowWindow(FALSE);
	GetDlgItem(IDC_STATIC_RECT)->ShowWindow(FALSE);
	GetDlgItem(IDC_STATIC_RECT_A)->ShowWindow(FALSE);
	GetDlgItem(IDC_STATIC_RECT_B)->ShowWindow(FALSE);
	GetDlgItem(IDC_STATIC_RECT_RESULT)->ShowWindow(FALSE);
	GetDlgItem(IDC_BUTTON_RECT)->ShowWindow(FALSE);
	GetDlgItem(IDC_EDIT_RECT_A)->ShowWindow(FALSE);
	GetDlgItem(IDC_EDIT_RECT_B)->ShowWindow(FALSE);
	GetDlgItem(IDC_EDIT_RECT_RESULT)->ShowWindow(FALSE);

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CTABAREADlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CTABAREADlg::OnPaint()
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
HCURSOR CTABAREADlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CTABAREADlg::OnSelchangeTabArea(NMHDR* pNMHDR, LRESULT* pResult)
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	int nSelect = m_tabArea.GetCurSel();

	switch (nSelect) {
	case 0:
		GetDlgItem(IDC_STATIC_TRI)->ShowWindow(TRUE);
		GetDlgItem(IDC_STATIC_TRI_A)->ShowWindow(TRUE);
		GetDlgItem(IDC_STATIC_TRI_B)->ShowWindow(TRUE);
		GetDlgItem(IDC_STATIC_TRI_RESULT)->ShowWindow(TRUE);
		GetDlgItem(IDC_BUTTON_TRI)->ShowWindow(TRUE);
		GetDlgItem(IDC_EDIT_TRI_A)->ShowWindow(TRUE);
		GetDlgItem(IDC_EDIT_TRI_B)->ShowWindow(TRUE);
		GetDlgItem(IDC_EDIT_TRI_RESULT)->ShowWindow(TRUE);

		GetDlgItem(IDC_STATIC_CIR)->ShowWindow(FALSE);
		GetDlgItem(IDC_STATIC_CIR_R)->ShowWindow(FALSE);
		GetDlgItem(IDC_STATIC_CIR_RESULT)->ShowWindow(FALSE);
		GetDlgItem(IDC_BUTTON_CIR)->ShowWindow(FALSE);
		GetDlgItem(IDC_EDIT_CIR_R)->ShowWindow(FALSE);
		GetDlgItem(IDC_EDIT_CIR_RESULT)->ShowWindow(FALSE);

		GetDlgItem(IDC_STATIC_RECT)->ShowWindow(FALSE);
		GetDlgItem(IDC_STATIC_RECT_A)->ShowWindow(FALSE);
		GetDlgItem(IDC_STATIC_RECT_B)->ShowWindow(FALSE);
		GetDlgItem(IDC_STATIC_RECT_RESULT)->ShowWindow(FALSE);
		GetDlgItem(IDC_BUTTON_RECT)->ShowWindow(FALSE);
		GetDlgItem(IDC_EDIT_RECT_A)->ShowWindow(FALSE);
		GetDlgItem(IDC_EDIT_RECT_B)->ShowWindow(FALSE);
		GetDlgItem(IDC_EDIT_RECT_RESULT)->ShowWindow(FALSE);
		break;
	case 1:
		GetDlgItem(IDC_STATIC_TRI)->ShowWindow(FALSE);
		GetDlgItem(IDC_STATIC_TRI_A)->ShowWindow(FALSE);
		GetDlgItem(IDC_STATIC_TRI_B)->ShowWindow(FALSE);
		GetDlgItem(IDC_STATIC_TRI_RESULT)->ShowWindow(FALSE);
		GetDlgItem(IDC_BUTTON_TRI)->ShowWindow(FALSE);
		GetDlgItem(IDC_EDIT_TRI_A)->ShowWindow(FALSE);
		GetDlgItem(IDC_EDIT_TRI_B)->ShowWindow(FALSE);
		GetDlgItem(IDC_EDIT_TRI_RESULT)->ShowWindow(FALSE);

		GetDlgItem(IDC_STATIC_CIR)->ShowWindow(TRUE);
		GetDlgItem(IDC_STATIC_CIR_R)->ShowWindow(TRUE);
		GetDlgItem(IDC_STATIC_CIR_RESULT)->ShowWindow(TRUE);
		GetDlgItem(IDC_BUTTON_CIR)->ShowWindow(TRUE);
		GetDlgItem(IDC_EDIT_CIR_R)->ShowWindow(TRUE);
		GetDlgItem(IDC_EDIT_CIR_RESULT)->ShowWindow(TRUE);

		GetDlgItem(IDC_STATIC_RECT)->ShowWindow(FALSE);
		GetDlgItem(IDC_STATIC_RECT_A)->ShowWindow(FALSE);
		GetDlgItem(IDC_STATIC_RECT_B)->ShowWindow(FALSE);
		GetDlgItem(IDC_STATIC_RECT_RESULT)->ShowWindow(FALSE);
		GetDlgItem(IDC_BUTTON_RECT)->ShowWindow(FALSE);
		GetDlgItem(IDC_EDIT_RECT_A)->ShowWindow(FALSE);
		GetDlgItem(IDC_EDIT_RECT_B)->ShowWindow(FALSE);
		GetDlgItem(IDC_EDIT_RECT_RESULT)->ShowWindow(FALSE);
		break;
	case 2:
		GetDlgItem(IDC_STATIC_TRI)->ShowWindow(FALSE);
		GetDlgItem(IDC_STATIC_TRI_A)->ShowWindow(FALSE);
		GetDlgItem(IDC_STATIC_TRI_B)->ShowWindow(FALSE);
		GetDlgItem(IDC_STATIC_TRI_RESULT)->ShowWindow(FALSE);
		GetDlgItem(IDC_BUTTON_TRI)->ShowWindow(FALSE);
		GetDlgItem(IDC_EDIT_TRI_A)->ShowWindow(FALSE);
		GetDlgItem(IDC_EDIT_TRI_B)->ShowWindow(FALSE);
		GetDlgItem(IDC_EDIT_TRI_RESULT)->ShowWindow(FALSE);

		GetDlgItem(IDC_STATIC_CIR)->ShowWindow(FALSE);
		GetDlgItem(IDC_STATIC_CIR_R)->ShowWindow(FALSE);
		GetDlgItem(IDC_STATIC_CIR_RESULT)->ShowWindow(FALSE);
		GetDlgItem(IDC_BUTTON_CIR)->ShowWindow(FALSE);
		GetDlgItem(IDC_EDIT_CIR_R)->ShowWindow(FALSE);
		GetDlgItem(IDC_EDIT_CIR_RESULT)->ShowWindow(FALSE);

		GetDlgItem(IDC_STATIC_RECT)->ShowWindow(TRUE);
		GetDlgItem(IDC_STATIC_RECT_A)->ShowWindow(TRUE);
		GetDlgItem(IDC_STATIC_RECT_B)->ShowWindow(TRUE);
		GetDlgItem(IDC_STATIC_RECT_RESULT)->ShowWindow(TRUE);
		GetDlgItem(IDC_BUTTON_RECT)->ShowWindow(TRUE);
		GetDlgItem(IDC_EDIT_RECT_A)->ShowWindow(TRUE);
		GetDlgItem(IDC_EDIT_RECT_B)->ShowWindow(TRUE);
		GetDlgItem(IDC_EDIT_RECT_RESULT)->ShowWindow(TRUE);
		break;
	}


	*pResult = 0;
}

void CTABAREADlg::OnClickedButtonCir()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(TRUE);
	m_dCirResult = 3.14 * m_dCirR * m_dCirR;
	UpdateData(FALSE);
}

void CTABAREADlg::OnClickedButtonRect()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(TRUE);
	m_dRectResult = m_dRectA * m_dRectB;
	UpdateData(FALSE);
}

void CTABAREADlg::OnClickedButtonTri()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(TRUE);
	m_dTriResult = (m_dTriA * m_dTriB) / 2;
	UpdateData(FALSE);
}

void CTABAREADlg::OnClickedButtonShow()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	AfxMessageBox(_T("원의넓이=반지름x반지름x3.14\n")
		_T("삼각형의넓이=밑변x높이/2\n")
		_T("사각형의넓이=가로x세로"));
}

void CTABAREADlg::OnClickedButtonExit()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	OnOK();
}
