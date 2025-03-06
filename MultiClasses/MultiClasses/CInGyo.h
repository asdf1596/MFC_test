﻿#pragma once
#include "afxdialogex.h"


// CInGyo 대화 상자

class CInGyo : public CDialogEx
{
	DECLARE_DYNAMIC(CInGyo)

public:
	CInGyo(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CInGyo();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_GYO_INPUT };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	CString m_strGyoIn1;
	CString m_strGyoIn2;
};
