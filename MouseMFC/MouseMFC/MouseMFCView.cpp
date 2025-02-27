
// MouseMFCView.cpp: CMouseMFCView 클래스의 구현
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "MouseMFC.h"
#endif

#include "MouseMFCDoc.h"
#include "MouseMFCView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMouseMFCView

IMPLEMENT_DYNCREATE(CMouseMFCView, CView)

BEGIN_MESSAGE_MAP(CMouseMFCView, CView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CMouseMFCView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_WM_MOUSEMOVE()
END_MESSAGE_MAP()

// CMouseMFCView 생성/소멸

CMouseMFCView::CMouseMFCView() noexcept
{
	// TODO: 여기에 생성 코드를 추가합니다.

}

CMouseMFCView::~CMouseMFCView()
{
}

BOOL CMouseMFCView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CView::PreCreateWindow(cs);
}

// CMouseMFCView 그리기

void CMouseMFCView::OnDraw(CDC* /*pDC*/)
{
	CMouseMFCDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.
	CClientDC dc(this);
	CString strPoint;
	strPoint.Format(_T("마우스 좌표(%4d, %4d)"), m_Pos.x, m_Pos.y);
	dc.TextOutW(0, 0, strPoint);
}


// CMouseMFCView 인쇄


void CMouseMFCView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CMouseMFCView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CMouseMFCView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CMouseMFCView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}

void CMouseMFCView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CMouseMFCView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CMouseMFCView 진단

#ifdef _DEBUG
void CMouseMFCView::AssertValid() const
{
	CView::AssertValid();
}

void CMouseMFCView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMouseMFCDoc* CMouseMFCView::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMouseMFCDoc)));
	return (CMouseMFCDoc*)m_pDocument;
}
#endif //_DEBUG


// CMouseMFCView 메시지 처리기

void CMouseMFCView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	m_Pos = point;
	Invalidate();

	CView::OnMouseMove(nFlags, point);
}
