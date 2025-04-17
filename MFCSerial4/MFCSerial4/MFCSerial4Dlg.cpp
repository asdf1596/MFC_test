// MFCSerial4Dlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "MFCSerial4.h"
#include "MFCSerial4Dlg.h"
#include "afxdialogex.h"
#include "SerialClass.h" // 시리얼 통신 클래스 추가
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();
private:
	Serial* m_pSerial;
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);

protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX) {}
void CAboutDlg::DoDataExchange(CDataExchange* pDX) { CDialogEx::DoDataExchange(pDX); }
BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()

// CMFCSerial4Dlg 대화 상자

CMFCSerial4Dlg::CMFCSerial4Dlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFCSERIAL4_DIALOG, pParent)
	, m_baud(0)
	, m_send(_T(""))
	, m_value(_T(""))
	, m_pSerial(nullptr)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

CMFCSerial4Dlg::~CMFCSerial4Dlg()
{
	if (m_pSerial)
	{
		delete m_pSerial;
		m_pSerial = nullptr;
	}
}

void CMFCSerial4Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_BAUD, m_baud);
	DDX_Text(pDX, IDC_EDIT_SEND, m_send);
	DDX_Text(pDX, IDC_EDIT_VALUE, m_value);
	DDX_Control(pDX, IDC_COMBO_PORT, m_ctrlPort);
}

BEGIN_MESSAGE_MAP(CMFCSerial4Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_REFIND, &CMFCSerial4Dlg::OnClickedButtonRefind)
	ON_BN_CLICKED(IDC_BUTTON_CONNECT, &CMFCSerial4Dlg::OnClickedButtonConnect)
END_MESSAGE_MAP()


// CMFCSerial4Dlg 메시지 처리기

BOOL CMFCSerial4Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

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

	SetIcon(m_hIcon, TRUE);
	SetIcon(m_hIcon, FALSE);

	return TRUE;
}

void CMFCSerial4Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CMFCSerial4Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this);

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

HCURSOR CMFCSerial4Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

// ✅ 포트 스캔 기능
void CMFCSerial4Dlg::OnClickedButtonRefind()
{
	m_ctrlPort.ResetContent();

	for (int i = 1; i <= 20; ++i)
	{
		CString portName;
		portName.Format(_T("\\\\.\\COM%d"), i);
		HANDLE hComm = CreateFile(portName, GENERIC_READ | GENERIC_WRITE, 0, nullptr, OPEN_EXISTING, 0, nullptr);

		if (hComm != INVALID_HANDLE_VALUE)
		{
			CloseHandle(hComm);

			CString displayName;
			displayName.Format(_T("COM%d"), i);
			m_ctrlPort.AddString(displayName);
		}
	}

	int count = m_ctrlPort.GetCount();
	if (count > 0)
		m_ctrlPort.SetCurSel(0);
	else
		AfxMessageBox(_T("사용 가능한 포트를 찾을 수 없습니다."));
}

// ✅ 포트 연결 기능
void CMFCSerial4Dlg::OnClickedButtonConnect()
{
	int selIndex = m_ctrlPort.GetCurSel();
	if (selIndex == CB_ERR)
	{
		AfxMessageBox(_T("포트를 선택하세요."));
		return;
	}

	CString selectedPort;
	m_ctrlPort.GetLBText(selIndex, selectedPort);
	CString fullPortName = _T("\\\\.\\") + selectedPort;

	UpdateData(TRUE);

	if (m_baud <= 0)
	{
		AfxMessageBox(_T("올바른 Baudrate를 입력하세요."));
		return;
	}

	if (m_pSerial)
	{
		delete m_pSerial;
		m_pSerial = nullptr;
	}

	m_pSerial = new Serial(CT2A(fullPortName), m_baud);

	if (m_pSerial->IsConnected())
	{
		AfxMessageBox(_T("포트 연결 성공!"));
	}
	else
	{
		AfxMessageBox(_T("포트 연결 실패."));
		delete m_pSerial;
		m_pSerial = nullptr;
	}
}
