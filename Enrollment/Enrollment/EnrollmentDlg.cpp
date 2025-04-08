
// EnrollmentDlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "Enrollment.h"
#include "EnrollmentDlg.h"
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


// CEnrollmentDlg 대화 상자



CEnrollmentDlg::CEnrollmentDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_ENROLLMENT_DIALOG, pParent)
	, m_strName(_T(""))
	, m_strNum(_T(""))
	, m_strCell(_T(""))
	, m_chA(FALSE)
	, m_chB(FALSE)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CEnrollmentDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_NAME, m_strName);
	DDX_Text(pDX, IDC_EDIT_NUM, m_strNum);
	DDX_Text(pDX, IDC_EDIT_CELL, m_strCell);
	DDX_Check(pDX, IDC_CHECK_A, m_chA);
	DDX_Check(pDX, IDC_CHECK_B, m_chB);
	DDX_Control(pDX, IDC_COMBO_POINT1, m_cbPoint1);
	DDX_Control(pDX, IDC_COMBO_POINT2, m_cbPoint2);
	DDX_Control(pDX, IDC_RADIO_ONLINE, m_rOnline);
	DDX_Control(pDX, IDC_LIST_VIEW, m_listView);
}

BEGIN_MESSAGE_MAP(CEnrollmentDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_INPUT, &CEnrollmentDlg::OnClickedButtonInput)
	ON_BN_CLICKED(IDC_BUTTON_DEL, &CEnrollmentDlg::OnClickedButtonDel)
	ON_BN_CLICKED(IDC_BUTTON_INIT, &CEnrollmentDlg::OnClickedButtonInit)
	ON_BN_CLICKED(IDC_BUTTON_EXIT, &CEnrollmentDlg::OnClickedButtonExit)
END_MESSAGE_MAP()


// CEnrollmentDlg 메시지 처리기

BOOL CEnrollmentDlg::OnInitDialog()
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
	for (int i = 1; i < 11; i++) {
		CString sIndex;
		sIndex.Format(_T("%d"), i);
		m_cbPoint1.AddString(sIndex);
	}

	for (int i = 1; i < 11; i++) {
		CString sIndex;
		sIndex.Format(_T("%d"), i);
		m_cbPoint2.AddString(sIndex);
	}

	char *szText[6] = { "학번", "이름","연락처","등록방법","시험유형","총배점" };
	int nWidth[6] = { 50,70,100,70,70,70 };

	LV_COLUMN iCol;
	iCol.mask = LVCF_FMT | LVCF_SUBITEM | LVCF_TEXT | LVCF_WIDTH;
	iCol.fmt = LVCFMT_LEFT;
	m_listView.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);

	for (int i = 0; i < 6; i++) {
		iCol.pszText = szText[i];
		iCol.iSubItem = i;
		iCol.cx = nWidth[i];
		m_listView.InsertColumn(i, &iCol);
	}

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CEnrollmentDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CEnrollmentDlg::OnPaint()
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
HCURSOR CEnrollmentDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CEnrollmentDlg::Init()
{
	// TODO: 여기에 구현 코드 추가.
	UpdateData(TRUE);
	CEdit* pEdit = (CEdit*)GetDlgItem(IDC_EDIT_NUM);
	m_strName.Empty();
	m_strNum.Empty();
	m_strCell.Empty();

	m_chA = m_chB = FALSE;

	m_rOnline.SetCheck(BST_UNCHECKED);

	m_cbPoint1.SetCurSel(0);
	m_cbPoint2.SetCurSel(0);

	pEdit->SetFocus();
	UpdateData(FALSE);

}

void CEnrollmentDlg::OnClickedButtonInput()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	char szText[100] = "";
	int nIndex = 0;
	UpdateData(TRUE);
	LVITEM iItem;
	iItem.mask = LVIF_TEXT;
	iItem.iItem = nIndex;

	iItem.iSubItem = 0;
	sprintf_s(szText, "%s", m_strNum);
	iItem.pszText = (LPSTR)szText;
	m_listView.InsertItem(&iItem);

	iItem.iSubItem = 1;
	sprintf_s(szText, "%s", m_strName);
	iItem.pszText = (LPSTR)szText;
	m_listView.SetItem(&iItem);

	iItem.iSubItem = 2;
	sprintf_s(szText, "%s", m_strCell);
	iItem.pszText = (LPSTR)szText;
	m_listView.SetItem(&iItem);

	iItem.iSubItem = 3;

	if (m_rOnline.GetCheck() == BST_CHECKED) {
		sprintf_s(szText, "%s", _T("온라인"));
	}
	else {
		sprintf_s(szText, "%s", _T("방문"));
	}

	iItem.pszText = (LPSTR)szText;
	m_listView.SetItem(&iItem);
	/////////////////////////////////////////

	CString selCombo1, selCombo2;
	if ((m_chA == TRUE) && (m_chB == FALSE)) {
		m_cbPoint1.GetLBText(m_cbPoint1.GetCurSel(), selCombo1);

		int cb10 = 0;
		int sum10 = 0;

		cb10 = _ttoi(selCombo1);
		sum10 = sum10 + cb10 * 20;

		iItem.iSubItem = 4;
		sprintf_s(szText, "%s", _T("주관식"));
		iItem.pszText = (LPSTR)szText;
		m_listView.SetItem(&iItem);

		iItem.iSubItem = 5;
		sprintf_s(szText, "%d", sum10);
		iItem.pszText = (LPSTR)szText;
		m_listView.SetItem(&iItem);

	}
	else if ((m_chA == FALSE) && (m_chB == TRUE)) {
		m_cbPoint2.GetLBText(m_cbPoint2.GetCurSel(), selCombo2);

		int cb20 = 0;
		int sum20 = 0;

		cb20 = _ttoi(selCombo2);
		sum20 = sum20 + cb20 * 10;

		iItem.iSubItem = 4;
		sprintf_s(szText, "%s", _T("객관식"));
		iItem.pszText = (LPSTR)szText;
		m_listView.SetItem(&iItem);

		iItem.iSubItem = 5;
		sprintf_s(szText, "%d", sum20);
		iItem.pszText = (LPSTR)szText;
		m_listView.SetItem(&iItem);
	}
	else if ((m_chA == TRUE) && (m_chB == TRUE)) {
		m_cbPoint1.GetLBText(m_cbPoint1.GetCurSel(), selCombo1);
		m_cbPoint2.GetLBText(m_cbPoint2.GetCurSel(), selCombo2);

		int cb30 = _ttoi(selCombo1);
		int cb31 = _ttoi(selCombo2);
		int sum30 = 0;

		sum30 = cb30 * 20 + cb31 * 10;

		iItem.iSubItem = 4;
		sprintf_s(szText, "%s", _T("혼합형"));
		iItem.pszText = (LPSTR)szText;
		m_listView.SetItem(&iItem);

		iItem.iSubItem = 5;
		sprintf_s(szText, "%d", sum30);
		iItem.pszText = (LPSTR)szText;
		m_listView.SetItem(&iItem);
	}
	else if ((m_chA == FALSE) && (m_chB == FALSE)) {
		MessageBox(_T("시험 유형을 선택하세요"), _T("입력에러"), MB_ICONSTOP | MB_OK);
	}
	Init();
	nIndex++;
	UpdateData(FALSE);
}

	


	void CEnrollmentDlg::OnClickedButtonDel()
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

	void CEnrollmentDlg::OnClickedButtonInit()
	{
		// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
		Init();
	}

	void CEnrollmentDlg::OnClickedButtonExit()
	{
		// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
		OnOK();
	}
