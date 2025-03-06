
// SEditGraphicView.h: CSEditGraphicView 클래스의 인터페이스
//

#pragma once


class CSEditGraphicView : public CView
{
protected: // serialization에서만 만들어집니다.
	CSEditGraphicView() noexcept;
	DECLARE_DYNCREATE(CSEditGraphicView)

// 특성입니다.
public:
	CSEditGraphicDoc* GetDocument() const;

// 작업입니다.
public:

// 재정의입니다.
public:
	virtual void OnDraw(CDC* pDC);  // 이 뷰를 그리기 위해 재정의되었습니다.
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 구현입니다.
public:
	virtual ~CSEditGraphicView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 생성된 메시지 맵 함수
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	int m_nOption;
	afx_msg void OnFigCir();
	afx_msg void OnFigApple();
	afx_msg void OnFigCross();
	afx_msg void OnFigRect();
	afx_msg void OnFigLine();
};

#ifndef _DEBUG  // SEditGraphicView.cpp의 디버그 버전
inline CSEditGraphicDoc* CSEditGraphicView::GetDocument() const
   { return reinterpret_cast<CSEditGraphicDoc*>(m_pDocument); }
#endif

