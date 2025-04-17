
// CountryTreeDlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "CountryTree.h"
#include "CountryTreeDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

char pszMenuAsiaInfo[6][100] = { "도쿄다","오사카다","부산이다","주성동이다","한남동이다","베이징이다" };
char pszMenuEuropeInfo[6][100] = { "뮌헨이다","베를린이다","런던이다","로마다","베네치아다","프랑스다" };


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


// CCountryTreeDlg 대화 상자



CCountryTreeDlg::CCountryTreeDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_COUNTRYTREE_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CCountryTreeDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TREE_ASIA, m_ctrAsia);
	DDX_Control(pDX, IDC_TREE_EUROPE, m_ctrEurope);
}

BEGIN_MESSAGE_MAP(CCountryTreeDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_CHINA, &CCountryTreeDlg::OnClickedButtonChina)
	ON_BN_CLICKED(IDC_BUTTON_FRANCE, &CCountryTreeDlg::OnClickedButtonFrance)
	ON_BN_CLICKED(IDC_BUTTON_UK, &CCountryTreeDlg::OnClickedButtonUk)
	ON_NOTIFY(TVN_SELCHANGED, IDC_TREE_ASIA, &CCountryTreeDlg::OnSelchangedTreeAsia)
	ON_NOTIFY(TVN_SELCHANGED, IDC_TREE_EUROPE, &CCountryTreeDlg::OnSelchangedTreeEurope)
END_MESSAGE_MAP()


// CCountryTreeDlg 메시지 처리기

BOOL CCountryTreeDlg::OnInitDialog()
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

	HTREEITEM hAsia;

	HTREEITEM hKor;
	HTREEITEM hJp;
	HTREEITEM hSeoul;
	HTREEITEM hGer;
	HTREEITEM hItl;
	HTREEITEM hYs;


	tInsert.hParent = 0;
	tInsert.hInsertAfter = TVI_SORT;
	tInsert.item.mask = TVIF_TEXT;
	tInsert.item.pszText = _T("동부아시아");
	hAsia = m_ctrAsia.InsertItem(&tInsert);

	tInsert.hParent = 0;
	tInsert.hInsertAfter = TVI_SORT;
	tInsert.item.mask = TVIF_TEXT;
	tInsert.item.pszText = _T("독일");
	hGer = m_ctrEurope.InsertItem(&tInsert);

	tInsert.hParent = 0;
	tInsert.hInsertAfter = TVI_SORT;
	tInsert.item.mask = TVIF_TEXT;
	tInsert.item.pszText = _T("이탈리아");
	hItl = m_ctrEurope.InsertItem(&tInsert);

	tInsert.hParent = hGer;
	tInsert.item.pszText = _T("뮌헨");
	m_ctrEurope.InsertItem(&tInsert);

	tInsert.hParent = hGer;
	tInsert.item.pszText = _T("베를린");
	m_ctrEurope.InsertItem(&tInsert);

	tInsert.hParent = hItl;
	tInsert.item.pszText = _T("로마");
	m_ctrEurope.InsertItem(&tInsert);

	tInsert.hParent = hItl;
	tInsert.item.pszText = _T("베네치아");
	m_ctrEurope.InsertItem(&tInsert);

	tInsert.hParent = hAsia;
	tInsert.item.pszText = _T("한국");
	hKor = m_ctrAsia.InsertItem(&tInsert);

	tInsert.hParent = hAsia;
	tInsert.item.pszText = _T("일본");	
	hJp = m_ctrAsia.InsertItem(&tInsert);

	tInsert.hParent = hJp;
	tInsert.item.pszText = _T("오사카");
	m_ctrAsia.InsertItem(&tInsert);

	tInsert.hParent = hJp;
	tInsert.item.pszText = _T("도쿄");
	m_ctrAsia.InsertItem(&tInsert);

	tInsert.hParent = hKor;
	tInsert.item.pszText = _T("부산");
	m_ctrAsia.InsertItem(&tInsert);

	tInsert.hParent = hKor;
	tInsert.item.pszText = _T("서울");
	hSeoul = m_ctrAsia.InsertItem(&tInsert);

	tInsert.hParent = hSeoul;
	tInsert.item.pszText = _T("용산구");
	hYs = m_ctrAsia.InsertItem(&tInsert);

	tInsert.hParent = hYs;
	tInsert.item.pszText = _T("주성동");
	m_ctrAsia.InsertItem(&tInsert);	

	tInsert.hParent = hYs;
	tInsert.item.pszText = _T("한남동");
	m_ctrAsia.InsertItem(&tInsert);


	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CCountryTreeDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CCountryTreeDlg::OnPaint()
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
HCURSOR CCountryTreeDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CCountryTreeDlg::OnClickedButtonChina()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	TVINSERTSTRUCT tInsert;
	HTREEITEM hChina;
	tInsert.hParent = 0;
	tInsert.hInsertAfter = TVI_SORT;
	tInsert.item.mask = TVIF_TEXT;
	tInsert.item.pszText = _T("중국");
	hChina = m_ctrAsia.InsertItem(&tInsert);

	tInsert.hParent = hChina;
	tInsert.item.pszText = _T("베이징");	
	m_ctrAsia.InsertItem(&tInsert);
}

void CCountryTreeDlg::OnClickedButtonFrance()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	TVINSERTSTRUCT tInsert;
	tInsert.hParent = 0;
	tInsert.hInsertAfter = TVI_SORT;
	tInsert.item.mask = TVIF_TEXT;
	tInsert.item.pszText = _T("프랑스");
	m_ctrEurope.InsertItem(&tInsert);
}

void CCountryTreeDlg::OnClickedButtonUk()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	TVINSERTSTRUCT tInsert;
	HTREEITEM hUk;
	tInsert.hParent = 0;
	tInsert.hInsertAfter = TVI_SORT;
	tInsert.item.mask = TVIF_TEXT;
	tInsert.item.pszText = _T("영국");
	hUk = m_ctrEurope.InsertItem(&tInsert);

	tInsert.hParent = hUk;
	tInsert.item.pszText = _T("런던");
	m_ctrEurope.InsertItem(&tInsert);

}

void CCountryTreeDlg::OnSelchangedTreeAsia(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	HTREEITEM hItemParent, hItemCur;
	CString strParent = _T("");
	CString strChild = _T("");

	hItemCur = pNMTreeView->itemNew.hItem;
	hItemParent = m_ctrAsia.GetParentItem(hItemCur);
	strChild = m_ctrAsia.GetItemText(hItemCur);
	strParent = m_ctrAsia.GetItemText(hItemParent);

	if (strParent == "일본") {
		if (strChild == "도쿄") {
			::SetDlgItemTextA(this->m_hWnd, IDC_EDIT_ASIA, pszMenuAsiaInfo[0]);
		}
		else if (strChild == "오사카") {
			::SetDlgItemTextA(this->m_hWnd, IDC_EDIT_ASIA, pszMenuAsiaInfo[1]);
		}
	}
	if (strParent == "한국") {
		if (strChild == "부산") {
			::SetDlgItemTextA(this->m_hWnd, IDC_EDIT_ASIA, pszMenuAsiaInfo[2]);
		}
	}
	if (strParent == "용산구") {
		if (strChild == "주성동") {
			::SetDlgItemTextA(this->m_hWnd, IDC_EDIT_ASIA, pszMenuAsiaInfo[3]);
		}
		else if (strChild == "한남동") {
			::SetDlgItemTextA(this->m_hWnd, IDC_EDIT_ASIA, pszMenuAsiaInfo[4]);
		}
	}
	if (strParent == "중국") {
		if (strChild == "베이징") {
			::SetDlgItemTextA(this->m_hWnd, IDC_EDIT_ASIA, pszMenuAsiaInfo[5]);
		}
	}
	*pResult = 0;
}

void CCountryTreeDlg::OnSelchangedTreeEurope(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.


	HTREEITEM hItemParent, hItemCur;
	hItemCur = pNMTreeView->itemNew.hItem;
	CString strParent = _T("");
	CString strChild = _T("");
	hItemParent = m_ctrEurope.GetParentItem(hItemCur);
	strChild = m_ctrEurope.GetItemText(hItemCur);
	strParent = m_ctrEurope.GetItemText(hItemParent);
	if (strParent == "독일") {
		if (strChild == "뮌헨") {
			::SetDlgItemTextA(this->m_hWnd, IDC_EDIT_EUROPE, pszMenuEuropeInfo[0]);
		}
		else if (strChild == "베를린") {
			::SetDlgItemTextA(this->m_hWnd, IDC_EDIT_EUROPE, pszMenuEuropeInfo[1]);
		}
	}
	if (strParent == "영국") {
		if (strChild == "런던") {
			::SetDlgItemTextA(this->m_hWnd, IDC_EDIT_EUROPE, pszMenuEuropeInfo[2]);
		}
	}
	if (strParent == "이탈리아") {
		if (strChild == "로마") {
			::SetDlgItemTextA(this->m_hWnd, IDC_EDIT_EUROPE, pszMenuEuropeInfo[3]);
		}
		else if (strChild == "베네치아") {
			::SetDlgItemTextA(this->m_hWnd, IDC_EDIT_EUROPE, pszMenuEuropeInfo[4]);
		}
	}
	if (strChild == "프랑스") {
		::SetDlgItemTextA(this->m_hWnd, IDC_EDIT_EUROPE, pszMenuEuropeInfo[5]);
	}

	*pResult = 0;
}
