#include "pch.h"
#include "framework.h"
#include "MFCSerial5.h"
#include "MFCSerial5Dlg.h"
#include "afxdialogex.h"
#include <windows.h>
#include <setupapi.h>
#include <string>
#include <vector>
#include <iostream>
#include <initguid.h>
#include <devguid.h>
#pragma comment(lib, "setupapi.lib")

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

std::vector<std::string> listAvailablePorts() {
	std::vector<std::string> ports;
	HDEVINFO hDevInfo = SetupDiGetClassDevs(&GUID_DEVCLASS_PORTS, 0, 0, DIGCF_PRESENT | DIGCF_PROFILE);
	if (hDevInfo == INVALID_HANDLE_VALUE) return ports;

	SP_DEVINFO_DATA devInfoData = {};
	devInfoData.cbSize = sizeof(SP_DEVINFO_DATA);
	char portName[256];

	for (DWORD i = 0; SetupDiEnumDeviceInfo(hDevInfo, i, &devInfoData); ++i) {
		HKEY hKey = SetupDiOpenDevRegKey(hDevInfo, &devInfoData, DICS_FLAG_GLOBAL, 0, DIREG_DEV, KEY_READ);
		if (hKey == INVALID_HANDLE_VALUE) continue;

		DWORD len = sizeof(portName);
		DWORD type = 0;
		if (RegQueryValueExA(hKey, "PortName", NULL, &type, (LPBYTE)portName, &len) == ERROR_SUCCESS) {
			ports.push_back(portName);
		}
		RegCloseKey(hKey);
	}
	SetupDiDestroyDeviceInfoList(hDevInfo);
	return ports;
}

CMFCSerial5Dlg::CMFCSerial5Dlg(CWnd* pParent)
	: CDialogEx(IDD_MFCSERIAL5_DIALOG, pParent), m_eBaud(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCSerial5Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_PORT, m_port);
	DDX_Text(pDX, IDC_EDIT_BAUD, m_eBaud);
	DDX_Control(pDX, IDC_EDIT_VALUE, m_editValue);
}

BEGIN_MESSAGE_MAP(CMFCSerial5Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_CONNECT, &CMFCSerial5Dlg::OnClickedButtonConnect)
	ON_BN_CLICKED(IDC_BUTTON_SCAN, &CMFCSerial5Dlg::OnClickedButtonScan)
	ON_BN_CLICKED(IDC_BUTTON_DISCONNECT, &CMFCSerial5Dlg::OnClickedButtonDisconnect)
	ON_MESSAGE(WM_USER + 1, &CMFCSerial5Dlg::OnSerialReceived)
END_MESSAGE_MAP()

BOOL CMFCSerial5Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	SetIcon(m_hIcon, TRUE);
	SetIcon(m_hIcon, FALSE);
	m_eBaud = 9600;
	UpdateData(FALSE);

	return TRUE;
}

void CMFCSerial5Dlg::OnPaint()
{
	if (IsIconic()) {
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
	else {
		CDialogEx::OnPaint();
	}
}

HCURSOR CMFCSerial5Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CMFCSerial5Dlg::OnClickedButtonScan()
{
	std::vector<std::string> ports = listAvailablePorts();
	m_port.ResetContent();

	if (ports.empty()) {
		MessageBox(_T("사용 가능한 COM 포트가 없습니다."), _T("오류"), MB_OK | MB_ICONERROR);
		return;
	}

	CString msg = _T("검색된 포트 목록:\n");
	for (const auto& p : ports) {
		CString name(p.c_str());
		m_port.AddString(name);
		msg += name + _T("\n");
	}

	MessageBox(msg, _T("포트 검색 결과"), MB_OK | MB_ICONINFORMATION);
}

void CMFCSerial5Dlg::OnClickedButtonConnect()
{
	int sel = m_port.GetCurSel();
	if (sel == CB_ERR) {
		MessageBox(_T("먼저 COM 포트를 선택하세요."), _T("오류"), MB_OK | MB_ICONWARNING);
		return;
	}

	CString selectedPort;
	m_port.GetLBText(sel, selectedPort);
	std::string portStr = CT2A(selectedPort);

	if (m_pSerial) {
		delete m_pSerial;
		m_pSerial = nullptr;
	}

	m_pSerial = new Serial(portStr.c_str(), m_eBaud);

	if (m_pSerial->IsConnected()) {
		MessageBox(_T("연결 성공!"), _T("알림"), MB_OK | MB_ICONINFORMATION);

		m_bRunningThread = true;
		m_pReadThread = AfxBeginThread(ReadDataThread, this);
	}
	else {
		MessageBox(_T("연결 실패..."), _T("오류"), MB_OK | MB_ICONERROR);
		delete m_pSerial;
		m_pSerial = nullptr;
	}
}

void CMFCSerial5Dlg::OnClickedButtonDisconnect()
{
	if (m_pSerial) {
		m_bRunningThread = false;

		if (m_pReadThread) {
			WaitForSingleObject(m_pReadThread->m_hThread, INFINITE);
			m_pReadThread = nullptr;
		}

		delete m_pSerial;
		m_pSerial = nullptr;

		MessageBox(_T("연결이 해제되었습니다."), _T("알림"), MB_OK | MB_ICONINFORMATION);
	}
	else {
		MessageBox(_T("해제할 연결이 없습니다."), _T("정보"), MB_OK | MB_ICONWARNING);
	}
}



UINT CMFCSerial5Dlg::ReadDataThread(LPVOID pParam)
{
	CMFCSerial5Dlg* pDlg = reinterpret_cast<CMFCSerial5Dlg*>(pParam);
	char incomingByte[1];
	std::string lineBuffer;

	while (pDlg->m_bRunningThread && pDlg->m_pSerial && pDlg->m_pSerial->IsConnected()) {
		int bytesRead = pDlg->m_pSerial->ReadData(incomingByte, 1);
		if (bytesRead > 0) {
			char ch = incomingByte[0];
			if (ch == '\n') {
				CString strValue(lineBuffer.c_str());
				::PostMessage(pDlg->m_hWnd, WM_USER + 1, 0, (LPARAM)new CString(strValue));
				lineBuffer.clear();
			}
			else if (ch != '\r') {
				lineBuffer += ch;
			}
		}
		Sleep(1);
	}

	return 0;
}	
LRESULT CMFCSerial5Dlg::OnSerialReceived(WPARAM wParam, LPARAM lParam)
{
	CString* pStr = reinterpret_cast<CString*>(lParam);
	if (pStr) {
		CString existingText;
		m_editValue.GetWindowText(existingText); // 기존 텍스트 읽기

		if (!existingText.IsEmpty())
			existingText += _T("\r\n");

		existingText += *pStr; // 새로운 줄 추가

		m_editValue.SetWindowText(existingText); // 텍스트 업데이트

		int nLineCount = m_editValue.GetLineCount();
		m_editValue.LineScroll(nLineCount); // 마지막 줄까지 스크롤

		delete pStr;
	}
	return 0;
}
