
// MemExDlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "MemEx.h"
#include "MemExDlg.h"
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


// CMemExDlg 대화 상자



CMemExDlg::CMemExDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MEMEX_DIALOG, pParent)
	, m_strCell(_T(""))      // 텍스트 초기화
	, m_strName(_T(""))      // 텍스트 초기화
	, m_nSelected(0)         // nSelected 변수 초기화
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}


void CMemExDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_CELL, m_strCell);
	DDX_Text(pDX, IDC_EDIT_NAME, m_strName);
	DDX_Control(pDX, IDC_RADIO_MOU, m_rMountain);
	DDX_Control(pDX, IDC_COMBO_POINT, m_cbPoint);
	DDX_Control(pDX, IDC_LIST_VIEW, m_listView);
}

BEGIN_MESSAGE_MAP(CMemExDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_INPUT, &CMemExDlg::OnClickedButtonInput)
	ON_BN_CLICKED(IDC_BUTTON_DEL, &CMemExDlg::OnClickedButtonDel)
	ON_BN_CLICKED(IDC_BUTTON_INIT, &CMemExDlg::OnClickedButtonInit)
	ON_BN_CLICKED(IDC_BUTTON_EXIT, &CMemExDlg::OnClickedButtonExit)
END_MESSAGE_MAP()


// CMemExDlg 메시지 처리기

BOOL CMemExDlg::OnInitDialog()
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

	char* szText[4] = { "Korea", "Japan","China","America" };
	char* szText2[4] = { "이름","연락처","선호관광지","선호국가"};
	for (int i = 0; i < 4; i++) {
		CString sIndex;
		sIndex.Format(_T("%s"), szText[i]);
		m_cbPoint.AddString(sIndex);
	}


	LV_COLUMN iCol;
	iCol.mask = LVCF_FMT | LVCF_SUBITEM | LVCF_TEXT | LVCF_WIDTH;
	iCol.fmt = LVCFMT_LEFT;
	m_listView.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);



	int nWidth[6] = { 50,50,70,70};
	for (int i = 0; i < 4; i++) {
		iCol.pszText = szText2[i];
		iCol.iSubItem = i;
		iCol.cx = nWidth[i];
		m_listView.InsertColumn(i, &iCol);
	}

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CMemExDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CMemExDlg::OnPaint()
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
HCURSOR CMemExDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CMemExDlg::Init()
{
	// TODO: 여기에 구현 코드 추가.
	UpdateData(TRUE);
	m_strName.Empty();
	m_strCell.Empty();

	m_rMountain.SetCheck(BST_UNCHECKED);

	m_cbPoint.SetCurSel(0);

	UpdateData(FALSE);
}

void CMemExDlg::OnClickedButtonInput()
{
	int nIndex = m_listView.GetItemCount();  // 리스트 뷰의 아이템 개수로 인덱스를 설정
	char szText[100] = "";
	UpdateData(TRUE);  // UI에서 데이터를 읽어옴

	LVITEM iItem;
	iItem.mask = LVIF_TEXT;
	iItem.iItem = nIndex;  // 새로운 항목 추가

	// 이름
	iItem.iSubItem = 0;
	// CString을 LPCTSTR로 변환하여 사용
	sprintf_s(szText, "%s", (LPCTSTR)m_strName);  // CString을 LPCTSTR로 변환
	iItem.pszText = szText;
	m_listView.InsertItem(&iItem);

	// 전화번호
	iItem.iSubItem = 1;
	sprintf_s(szText, "%s", (LPCTSTR)m_strCell);  // CString을 LPCTSTR로 변환
	iItem.pszText = szText;
	m_listView.SetItem(&iItem);

	// 산/바다
	iItem.iSubItem = 2;
	if (m_rMountain.GetCheck() == BST_CHECKED) {
		sprintf_s(szText, "%s", _T("산"));
	}
	else {
		sprintf_s(szText, "%s", _T("바다"));
	}
	iItem.pszText = szText;
	m_listView.SetItem(&iItem);

	// 점수
	CString selCombo;
	m_cbPoint.GetLBText(m_cbPoint.GetCurSel(), selCombo);
	iItem.iSubItem = 3;
	// CString을 LPCTSTR로 변환하여 사용
	sprintf_s(szText, "%s", (LPCTSTR)selCombo);  // CString을 LPCTSTR로 변환
	iItem.pszText = szText;
	m_listView.SetItem(&iItem);

	// 초기화
	Init();  // 입력 필드를 초기화

	UpdateData(FALSE);  // UI 업데이트
}

void CMemExDlg::OnClickedButtonDel()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	for (int nItem = 0; nItem < m_listView.GetItemCount();) {
		if (m_listView.GetItemState(nItem, LVIS_SELECTED) == LVIS_SELECTED) {
			m_listView.DeleteItem(nItem);
		}
		else {
			++nItem;
		}
	}
	UpdateData(FALSE);

}

void CMemExDlg::OnClickedButtonInit()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	Init();
}

void CMemExDlg::OnClickedButtonExit()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	OnOK();
}
