// MFCSerial5Dlg.h

#pragma once
#include "SerialClass.h"
#include <string>

class CMFCSerial5Dlg : public CDialogEx
{
	// 생성입니다.
public:
	CMFCSerial5Dlg(CWnd* pParent = nullptr);

	// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFCSERIAL5_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);
	CString FormatByBase(int value, const CString& direction);

protected:
	HICON m_hIcon;

	// 사용자 정의 추가
	Serial* m_pSerial = nullptr;
	CWinThread* m_pReadThread = nullptr;
	bool m_bRunningThread = false;

	static UINT ReadDataThread(LPVOID pParam);
	// 구현입니다.
protected:
	DECLARE_MESSAGE_MAP()
	DWORD m_lastDataTime; // 마지막 데이터 수신 시간
	static const DWORD TIMEOUT_MS = 5000; // 5초 타임아웃
	bool m_bReconnecting; // 재연결 중 플래그

	// 메시지 핸들러 선언
	afx_msg LRESULT OnReconnect(WPARAM wParam, LPARAM lParam);
public:
	CComboBox m_port;
	int m_eBaud;
	CEdit m_editValue; // ← 멤버 변수 선언
	// 클래스 선언 중간에 추가:
	afx_msg LRESULT OnSerialReceived(WPARAM wParam, LPARAM lParam);

	afx_msg void OnClickedButtonConnect();
	afx_msg void OnClickedButtonDisconnect();
	afx_msg void OnClickedButtonScan();
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnClickedButtonSend();
	CString m_eSend;
	CButton m_cDec;
	CButton m_cHex;
	CButton m_cOct;
	afx_msg void OnClickedCheckDec();
	afx_msg void OnClickedCheckHex();
	afx_msg void OnClickedCheckOct();
	afx_msg void OnBnClickedButtonExit();
};
