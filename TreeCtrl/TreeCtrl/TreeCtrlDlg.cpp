
// TreeCtrlDlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "TreeCtrl.h"
#include "TreeCtrlDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

char pszMenuJuiceInfo[2][100] = { "사과로 만든 주스","오렌지로 만든 주스" };
char pszMenuCoffeeInfo[3][100] = { "향이 좋은 따뜻한 coffee","시원한 아이스커피","달콤한 커피" };
char pszMenuDessertInfo[3][100] = { "신선한 바닐라 아이스크림","초콜릿이 듬뿍 들어간 초코 케이크","촉촉하고 부드러운 치즈 케이크"};



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


// CTreeCtrlDlg 대화 상자



CTreeCtrlDlg::CTreeCtrlDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_TREECTRL_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CTreeCtrlDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TREE_MENU, m_ctrMenu);
}

BEGIN_MESSAGE_MAP(CTreeCtrlDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_DESSERT, &CTreeCtrlDlg::OnClickedButtonDessert)
	ON_BN_CLICKED(IDC_BUTTON_DRINK, &CTreeCtrlDlg::OnClickedButtonDrink)
	ON_BN_CLICKED(IDC_BUTTON_EXIT, &CTreeCtrlDlg::OnClickedButtonExit)
	ON_NOTIFY(TVN_SELCHANGED, IDC_TREE_MENU, &CTreeCtrlDlg::OnSelchangedTreeMenu)
END_MESSAGE_MAP()


// CTreeCtrlDlg 메시지 처리기

BOOL CTreeCtrlDlg::OnInitDialog()
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

	TVINSERTSTRUCT tInsert;
	HTREEITEM hDrink;
	HTREEITEM hDrinkCoffee;
	HTREEITEM hHotCold;

	tInsert.hParent = 0;
	tInsert.hInsertAfter = TVI_SORT;
	tInsert.item.mask = TVIF_TEXT;
	tInsert.item.pszText = _T("음료");
	hDrink = m_ctrMenu.InsertItem(&tInsert);

	tInsert.hParent = hDrink;
	tInsert.item.pszText = _T("커피");
	hDrinkCoffee = m_ctrMenu.InsertItem(&tInsert);

	tInsert.hParent = hDrink;
	tInsert.item.pszText = _T("아메리카노");
	hHotCold = m_ctrMenu.InsertItem(&tInsert);

	tInsert.hParent = hHotCold;
	tInsert.item.pszText = _T("따뜻한 아메리카노");
	m_ctrMenu.InsertItem(&tInsert);

	tInsert.hParent = hDrinkCoffee;
	tInsert.item.pszText = _T("카푸치노");
	m_ctrMenu.InsertItem(&tInsert);

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CTreeCtrlDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CTreeCtrlDlg::OnPaint()
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
HCURSOR CTreeCtrlDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CTreeCtrlDlg::OnClickedButtonDessert()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	TVINSERTSTRUCT tInsert;

	HTREEITEM hDessert;

	HTREEITEM DessertSort;

	tInsert.hParent = 0;
	tInsert.hInsertAfter = TVI_SORT;
	tInsert.item.mask = TVIF_TEXT;
	tInsert.item.pszText = _T("디저트");
	hDessert = m_ctrMenu.InsertItem(&tInsert);

	tInsert.hParent = hDessert;
	tInsert.item.pszText = _T("케이크");
	DessertSort = m_ctrMenu.InsertItem(&tInsert);

	tInsert.hParent = DessertSort;
	tInsert.item.pszText = _T("초코 케이크");
	m_ctrMenu.InsertItem(&tInsert);

	tInsert.hParent = DessertSort;
	tInsert.item.pszText = _T("치즈 케이크");
	m_ctrMenu.InsertItem(&tInsert);

	tInsert.hParent = hDessert;
	tInsert.item.pszText = _T("아이스크림");
	hDessert = m_ctrMenu.InsertItem(&tInsert);
}

void CTreeCtrlDlg::OnClickedButtonDrink()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	TVINSERTSTRUCT tInsert;

	HTREEITEM hOtherDrink;

	HTREEITEM hDrinkJuice;

	tInsert.hParent = 0;
	tInsert.hInsertAfter = TVI_SORT;
	tInsert.item.mask = TVIF_TEXT;
	tInsert.item.pszText = _T("기타 음료");
	hOtherDrink = m_ctrMenu.InsertItem(&tInsert);

	tInsert.hParent = hOtherDrink;
	tInsert.item.pszText = _T("주스");
	hDrinkJuice = m_ctrMenu.InsertItem(&tInsert);


	tInsert.hParent = hDrinkJuice;
	tInsert.item.pszText = _T("사과");
	m_ctrMenu.InsertItem(&tInsert);

	tInsert.hParent = hDrinkJuice;
	tInsert.item.pszText = _T("오렌지");
	m_ctrMenu.InsertItem(&tInsert);
}

void CTreeCtrlDlg::OnClickedButtonExit()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	OnOK();
}

void CTreeCtrlDlg::OnSelchangedTreeMenu(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	HTREEITEM hItemParent, hItemCur;
	CString strParent = _T("");
	CString strChild = _T("");

	hItemCur = pNMTreeView->itemNew.hItem;
	hItemParent = m_ctrMenu.GetParentItem(hItemCur);
	strChild = m_ctrMenu.GetItemText(hItemCur);
	strParent = m_ctrMenu.GetItemText(hItemParent);

	if (strParent == "주스") {
		if (strChild == "사과") {
			::SetDlgItemTextA(this->m_hWnd, IDC_EDIT_MENUINFO, pszMenuJuiceInfo[0]);
		}
		else if (strChild == "오렌지") {
			::SetDlgItemTextA(this->m_hWnd, IDC_EDIT_MENUINFO, pszMenuJuiceInfo[1]);
		}
	}
	if (strParent == "아메리카노") {
		if (strChild == "따뜻한 아메리카노") {
			::SetDlgItemTextA(this->m_hWnd, IDC_EDIT_MENUINFO, pszMenuCoffeeInfo[0]);
		}
		else if (strChild == "아이스 아메리카노") {
			::SetDlgItemTextA(this->m_hWnd, IDC_EDIT_MENUINFO, pszMenuCoffeeInfo[1]);
		}	
	}
	if (strParent == "커피") {
		if (strChild == "카푸치노") {
			::SetDlgItemTextA(this->m_hWnd, IDC_EDIT_MENUINFO, pszMenuCoffeeInfo[2]);
		}
	}
	if (strParent == "디저트") {
		if (strChild == "아이스크림") {
			::SetDlgItemTextA(this->m_hWnd, IDC_EDIT_MENUINFO, pszMenuDessertInfo[0]);
		}
	}
	if (strParent == "케이크") {
		if (strChild == "초코 케이크") {
			::SetDlgItemTextA(this->m_hWnd, IDC_EDIT_MENUINFO, pszMenuDessertInfo[1]);
		}
		else if (strChild == "치즈 케이크") {
			::SetDlgItemTextA(this->m_hWnd, IDC_EDIT_MENUINFO, pszMenuDessertInfo[2]);
		}
	}
	*pResult = 0;
}
