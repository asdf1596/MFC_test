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
#include <deque>
#include <devguid.h>
#include <fstream>
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
	, m_eSend(_T(""))
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
	ON_BN_CLICKED(IDC_BUTTON_EXIT, &CMFCSerial5Dlg::OnBnClickedButtonExit)
	ON_WM_TIMER()
END_MESSAGE_MAP()

BOOL CMFCSerial5Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	SetIcon(m_hIcon, TRUE);
	SetIcon(m_hIcon, FALSE);
	m_eBaud = 9600;
	m_lastDataTime = GetTickCount64(); // 타임아웃 초기화
	m_bReconnecting = false; // 재연결 플래그 초기화
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

	//MessageBox(msg, _T("포트 검색 결과"), MB_OK | MB_ICONINFORMATION);
}

void CMFCSerial5Dlg::OnClickedButtonConnect()
{
	// 버튼 캡션 변경
	CButton* pButton = (CButton*)GetDlgItem(IDC_BUTTON_CONNECT); // 버튼 ID로 변경
	pButton->SetWindowText(_T("연결중.."));

	// 기존 코드
	m_bRunningThread = false;

	if (m_pReadThread) {
		WaitForSingleObject(m_pReadThread->m_hThread, INFINITE);
		m_pReadThread = nullptr;
	}

	delete m_pSerial;
	m_pSerial = nullptr;

	int sel = m_port.GetCurSel();
	if (sel == CB_ERR) {
		MessageBox(_T("먼저 COM 포트를 선택하세요."), _T("오류"), MB_OK | MB_ICONWARNING);
		pButton->SetWindowText(_T("연결")); // 원래 캡션 복원
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
		// 연결 성공 후 1초 대기 후 캡션 복원
		SetTimer(1, 1000, nullptr); // 1초 타이머 설정
		m_bRunningThread = true;
		m_pReadThread = AfxBeginThread(ReadDataThread, this);
	}
	else {
		MessageBox(_T("연결 실패..."), _T("오류"), MB_OK | MB_ICONERROR);
		delete m_pSerial;
		m_pSerial = nullptr;
		pButton->SetWindowText(_T("연결")); // 원래 캡션 복원
	}
}

// 타이머 핸들러 추가
void CMFCSerial5Dlg::OnTimer(UINT_PTR nIDEvent)
{
	if (nIDEvent == 1) {
		CButton* pButton = (CButton*)GetDlgItem(IDC_BUTTON_CONNECT); // 버튼 ID로 변경
		pButton->SetWindowText(_T("연결")); // 원래 캡션 복원
		KillTimer(1); // 타이머 종료
	}
	CDialogEx::OnTimer(nIDEvent);
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

		//MessageBox(_T("연결이 해제되었습니다."), _T("알림"), MB_OK | MB_ICONINFORMATION);
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

	pDlg->m_lastDataTime = GetTickCount();
	pDlg->m_bReconnecting = false;

	while (pDlg->m_bRunningThread) {
		if (pDlg->m_pSerial && pDlg->m_pSerial->IsConnected()) {
			int bytesRead = pDlg->m_pSerial->ReadData(incomingByte, 1);
			if (bytesRead > 0) {
				pDlg->m_lastDataTime = GetTickCount();
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
			else {
				if (GetTickCount() - pDlg->m_lastDataTime > TIMEOUT_MS && !pDlg->m_bReconnecting) {
					pDlg->m_bReconnecting = true;
					::PostMessage(pDlg->m_hWnd, WM_USER + 2, 0, 0);
				}
			}
		}
		else {
			if (!pDlg->m_bReconnecting) {
				pDlg->m_bReconnecting = true;
				::PostMessage(pDlg->m_hWnd, WM_USER + 2, 0, 0);
			}
		}
		Sleep(1);
	}

	return 0;
}
//void WriteToCSV(const CString& data, const CString& direction)
//{
//	CString logFilePath = _T("C:\\Users\\infor\\OneDrive\\바탕 화면\\log_test\\chat_log4.csv");
//
//	// 파일이 처음 생성될 때 헤더 추가
//	BOOL fileExists = PathFileExists(logFilePath);
//	std::ofstream file(CT2A(logFilePath), std::ios::app);
//
//	if (file.is_open()) {
//		if (!fileExists) {
//			file << "시간,방향,값\n";
//		}
//
//		SYSTEMTIME st;
//		GetLocalTime(&st);
//
//		char timeBuffer[100];
//		snprintf(timeBuffer, sizeof(timeBuffer), "%04d-%02d-%02d %02d:%02d:%02d",
//			st.wYear, st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond);
//
//		file << timeBuffer << "," << CStringA(direction) << "," << CStringA(data) << std::endl;
//		file.close();
//	}
//	else {
//		AfxMessageBox(_T("CSV 파일을 열 수 없습니다."), MB_ICONERROR);
//	}
//}



enum RadixType { RADIX_DEC, RADIX_HEX, RADIX_OCT };

RadixType GetSelectedRadix(CMFCSerial5Dlg* dlg) {
	if (dlg->m_cHex.GetCheck()) return RADIX_HEX;
	return RADIX_DEC;
}

LRESULT CMFCSerial5Dlg::OnSerialReceived(WPARAM wParam, LPARAM lParam)
{
	static std::deque<CString> recentValues;  // 최신 값 5개 저장용

	CString* pStr = reinterpret_cast<CString*>(lParam);
	if (pStr) {
		int value = _ttoi(*pStr);  // 10진수로 파싱
		CString formattedValue = FormatByBase(value, _T("RX"));

		// 큐에 새 값 추가
		recentValues.push_back(formattedValue);

		// 최대 5개 유지
		if (recentValues.size() > 5)
			recentValues.pop_front();

		// 전체 출력 문자열 조합
		CString displayText;
		for (const auto& val : recentValues) {
			displayText += val + _T("\r\n");
		}

		// UI에 출력
		m_editValue.SetWindowText(displayText);
		m_editValue.LineScroll(m_editValue.GetLineCount());

		delete pStr;
	}
	return 0;
}

CString CMFCSerial5Dlg::FormatByBase(int value, const CString& direction)
{
	CString result;

	if (m_cHex.GetCheck()) {
		result.Format(_T("0x%X"), value); // 16진수 형식으로 변환
	}
	else {
		result.Format(_T("%d"), value);   // 10진수 형식으로 변환
	}

	return result;
}


bool IsNumeric(const CString& str)
{
	for (int i = 0; i < str.GetLength(); ++i) {
		if (!isdigit(str[i])) return false;
	}
	return !str.IsEmpty();
}

bool IsHexString(const CString& str)
{
	for (int i = 0; i < str.GetLength(); ++i) {
		if (!isxdigit(str[i])) return false;
	}
	return !str.IsEmpty();
}



void CMFCSerial5Dlg::OnClickedButtonSend()
{
	if (m_pSerial && m_pSerial->IsConnected()) {
		CString strToSend;
		//GetDlgItem(IDC_EDIT_SEND)->GetWindowText(strToSend);

		strToSend.Trim();  // 앞뒤 공백 제거
		CString formattedValue;
		std::string sendStr;

		if (GetSelectedRadix(this) == RADIX_HEX && IsHexString(strToSend)) {
			// 16진수 문자열 -> 숫자로 변환
			unsigned int value = _tcstoul(strToSend, NULL, 16);
			formattedValue.Format(_T("0x%X"), value);
			sendStr = CStringA(strToSend);  // 그대로 전송
		}
		else if (IsNumeric(strToSend)) {
			// 10진수 문자열
			int value = _ttoi(strToSend);
			switch (GetSelectedRadix(this)) {
			case RADIX_DEC:
				formattedValue.Format(_T("%d"), value);
				break;
			case RADIX_HEX:
				formattedValue.Format(_T("0x%X"), value);
				break;
			case RADIX_OCT:
				formattedValue.Format(_T("%o"), value);
				break;
			}
			sendStr = CStringA(strToSend);  // 그대로 전송
		}
		else {
			// 숫자가 아닌 일반 문자 (예: a, A)
			formattedValue = strToSend;
			sendStr = CStringA(strToSend);
		}

		// 전송
		m_pSerial->WriteData(sendStr.c_str(), sendStr.length());

		// 로그 출력
		CString existingText;
		m_editValue.GetWindowText(existingText);
		if (!existingText.IsEmpty()) existingText += _T("\r\n");
		existingText += _T("[TX] ") + formattedValue;
		m_editValue.SetWindowText(existingText);
		m_editValue.LineScroll(m_editValue.GetLineCount());

		//WriteToCSV(formattedValue, _T("TX"));
	}
	else {
		MessageBox(_T("시리얼이 연결되어 있지 않습니다."), _T("오류"), MB_OK | MB_ICONERROR);
	}
}



void CMFCSerial5Dlg::OnClickedCheckDec()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	m_cHex.SetCheck(FALSE);
	//m_cOct.SetCheck(FALSE);
}

void CMFCSerial5Dlg::OnClickedCheckHex()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	m_cDec.SetCheck(FALSE);
	//m_cOct.SetCheck(FALSE);
}

void CMFCSerial5Dlg::OnClickedCheckOct()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	m_cDec.SetCheck(FALSE);
	m_cHex.SetCheck(FALSE);
}

void CMFCSerial5Dlg::OnBnClickedButtonExit()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (m_pSerial) {
		m_bRunningThread = false;

		if (m_pReadThread) {
			WaitForSingleObject(m_pReadThread->m_hThread, INFINITE);
			m_pReadThread = nullptr;
		}

		delete m_pSerial;
		m_pSerial = nullptr;

		//MessageBox(_T("연결이 해제되었습니다."), _T("알림"), MB_OK | MB_ICONINFORMATION);
	}
	OnOK();
}
