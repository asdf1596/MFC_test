
// MultiExView.cpp: CMultiExView 클래스의 구현
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "MultiEx.h"
#endif

#include "MultiExDoc.h"
#include "MultiExView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMultiExView

IMPLEMENT_DYNCREATE(CMultiExView, CView)

BEGIN_MESSAGE_MAP(CMultiExView, CView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CMultiExView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
END_MESSAGE_MAP()

// CMultiExView 생성/소멸

CMultiExView::CMultiExView() noexcept
{
	// TODO: 여기에 생성 코드를 추가합니다.

}

CMultiExView::~CMultiExView()
{
}

BOOL CMultiExView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CView::PreCreateWindow(cs);
}

// CMultiExView 그리기

void CMultiExView::OnDraw(CDC* pDC)
{
	CMultiExDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.
	RECT rect;
	rect.left = m_ptX+200;
	rect.top = m_ptY-100;
	rect.right = m_ptX + 300;
	rect.bottom = m_ptY - 0;
	pDC->SelectStockObject(GRAY_BRUSH);
	pDC->Rectangle(&rect);
	pDC->SelectStockObject(BLACK_BRUSH);
	pDC->Ellipse(m_ptX, m_ptY, m_ptX + 140, m_ptY + 140);
	pDC->TextOutW(20, 20, _T("사각형/타원 그리기 다중 예제"));

}


// CMultiExView 인쇄


void CMultiExView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CMultiExView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CMultiExView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CMultiExView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}

void CMultiExView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CMultiExView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CMultiExView 진단

#ifdef _DEBUG
void CMultiExView::AssertValid() const
{
	CView::AssertValid();
}

void CMultiExView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMultiExDoc* CMultiExView::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMultiExDoc)));
	return (CMultiExDoc*)m_pDocument;
}
#endif //_DEBUG


// CMultiExView 메시지 처리기

void CMultiExView::OnInitialUpdate()
{
	CView::OnInitialUpdate();

	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	CMultiExDoc* pDoc = GetDocument();

	m_ptX = pDoc->m_ptX;
	m_ptY = pDoc->m_ptY;

}
