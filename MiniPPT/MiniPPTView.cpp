
// MiniPPTView.cpp: CMiniPPTView 클래스의 구현
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "MiniPPT.h"
#endif

#include "MiniPPTDoc.h"
#include "MiniPPTView.h"

#include "CMyShape.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMiniPPTView

IMPLEMENT_DYNCREATE(CMiniPPTView, CView)

BEGIN_MESSAGE_MAP(CMiniPPTView, CView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_PAINT()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOVE()
	ON_WM_DESTROY()
	ON_COMMAND(ID_SHAPE_BRUSHRED, &CMiniPPTView::OnShapeBrushred)
	ON_COMMAND(ID_SHAPE_BRUSHGREEN, &CMiniPPTView::OnShapeBrushgreen)
	ON_COMMAND(ID_SHAPE_BRUSHBLUE, &CMiniPPTView::OnShapeBrushblue)
	ON_UPDATE_COMMAND_UI(ID_SHAPE_BRUSHRED, &CMiniPPTView::OnUpdateShapeBrushred)
	ON_UPDATE_COMMAND_UI(ID_SHAPE_BRUSHGREEN, &CMiniPPTView::OnUpdateShapeBrushgreen)
	ON_UPDATE_COMMAND_UI(ID_SHAPE_BRUSHBLUE, &CMiniPPTView::OnUpdateShapeBrushblue)
END_MESSAGE_MAP()

// CMiniPPTView 생성/소멸

CMiniPPTView::CMiniPPTView() noexcept
{
	// TODO: 여기에 생성 코드를 추가합니다.

}

CMiniPPTView::~CMiniPPTView()
{
}

BOOL CMiniPPTView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CView::PreCreateWindow(cs);
}

// CMiniPPTView 그리기

void CMiniPPTView::OnDraw(CDC* /*pDC*/)
{
	CMiniPPTDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.
}


// CMiniPPTView 인쇄

BOOL CMiniPPTView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CMiniPPTView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CMiniPPTView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}


// CMiniPPTView 진단

#ifdef _DEBUG
void CMiniPPTView::AssertValid() const
{
	CView::AssertValid();
}

void CMiniPPTView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMiniPPTDoc* CMiniPPTView::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMiniPPTDoc)));
	return (CMiniPPTDoc*)m_pDocument;
}
#endif //_DEBUG


// CMiniPPTView 메시지 처리기

void CMiniPPTView::OnPaint()
{
	CPaintDC dc(this); // device context for painting

	CMyShape* pShape = NULL;

	POSITION pos =  m_listShape.GetHeadPosition();
	
	while (pos != NULL) {
		// 주소를 가져와라
		pShape = (CMyShape*)m_listShape.GetAt(pos);

		CPen pen(PS_SOLID, pShape->m_nPenWidth, pShape->m_cPen);
		CPen *pOldPen = dc.SelectObject(&pen);

		CBrush brush(pShape->m_cBrush);
		CBrush* pOldBrush = dc.SelectObject(&brush);

		dc.Rectangle(
			pShape->m_point.x, pShape->m_point.y,
			pShape->m_point.x + pShape->m_size.cx,
			pShape->m_point.y + pShape->m_size.cy
		);

		dc.SelectObject(pOldPen);
		dc.SelectObject(pOldBrush);

		// 루프 돌기
		m_listShape.GetNext(pos);
	}
}

void CMiniPPTView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// 어떤 도형을 찾아보자
	// 도형안에 있는지 찾아서 있다면 주소 반환
	// 도형 리스트를 돌면서 이 점이 어떤 도형 안에 있냐를 찾고,
	// 찾으면 그 도형의 주소를 반환.
	// 못찾으면 null/nullptr 반환
	CMyShape* pShape = PtInShapes(point);

	if (pShape != NULL) {
		// 선택된 도형을 위로 올리기

		// m_listShape 안에서 방금 선택된 도형 pShape가 들어있는 위치 찾기
		// POSITION : 위치 값
		POSITION pos = m_listShape.Find(pShape);

		// 연결 리스트에서 선택된 도형을 현재 리스트에서 빼내기
		// 연결 위치만 제거(pShape 포인터는 살아있음)
		m_listShape.RemoveAt(pos);

		// 방금 뺀 도형을 리스트의 맨 뒤에 다시 넣기(최상단으로 올린 것처럼 보이기)
		m_listShape.AddTail(pShape);
		// OnPaint()에서 도형을 그릴 때 
		// 리스트의 앞에서부터 뒤까지 순서대로 그리기 때문
		RedrawWindow();
	}
	else {
		// 그리기
		m_bDraw = TRUE;
	}


	// 좌표 저장
	m_ptBegin = point;

	CView::OnLButtonDown(nFlags, point);
}

void CMiniPPTView::OnLButtonUp(UINT nFlags, CPoint point)
{
	if (m_bDraw) {

		m_ptEnd = point;

	// 그리기 끝
	m_bDraw = FALSE;	

	// 새 도형이 생성되어야함
	CMyShape *pNewShape = new CMyShape;
	//pNewShape->m_point = m_ptBegin;
	//pNewShape->m_size = m_ptEnd - m_ptBegin;

	// 끝지점이 시작지점보다 작을 경우 대비
	pNewShape->m_point.x =
		(m_ptBegin.x < m_ptEnd.x) ? m_ptBegin.x : m_ptEnd.x;
	pNewShape->m_point.y =
		(m_ptBegin.y < m_ptEnd.y) ? m_ptBegin.y : m_ptEnd.y;

	pNewShape->m_size = m_ptEnd - m_ptBegin;
	pNewShape->m_size.cx = abs(pNewShape->m_size.cx);
	pNewShape->m_size.cy = abs(pNewShape->m_size.cy);

	// 색상 넣기(현재 view class의 m_cBrush를 넣기)
	pNewShape->m_cBrush = this->m_cBrush;

	// 연결리스트
	m_listShape.AddTail(pNewShape);
	RedrawWindow();
	}



	CView::OnLButtonUp(nFlags, point);
}

void CMiniPPTView::OnMove(int x, int y)
{
	CView::OnMove(x, y);

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
}


CMyShape* CMiniPPTView::PtInShapes(CPoint point)
{
	CMyShape* pShape = NULL;

	POSITION pos = m_listShape.GetHeadPosition();

	while (pos != NULL) {
		// 주소를 가져와라
		pShape = (CMyShape*)m_listShape.GetAt(pos);

		if (pShape->PtInShape(point))
		{
			return pShape;
		}

		// 루프 돌기
		m_listShape.GetNext(pos);
	}

	return nullptr;
}

void CMiniPPTView::ReleaseList()
{
	CMyShape* pShape = NULL;

	POSITION pos = m_listShape.GetHeadPosition();

	while (pos != NULL) {
		// 주소를 가져와라
		pShape = (CMyShape*)m_listShape.GetAt(pos);

		// delete (new로 생성했던 pShape 객체를 delete)
		delete pShape;

		// 루프 돌기
		m_listShape.GetNext(pos);
	}

	m_listShape.RemoveAll();
}

// 뷰 객체가 완전히 소멸할 때 호출됨 (윈도우 객체가 사라질 때)
void CMiniPPTView::OnDestroy()
{
	CView::OnDestroy();

	ReleaseList();
}

void CMiniPPTView::OnShapeBrushred()
{
	m_cBrush = RGB(255, 0, 0);
}

void CMiniPPTView::OnShapeBrushgreen()
{
	m_cBrush = RGB(0, 255, 0);
}

void CMiniPPTView::OnShapeBrushblue()
{
	m_cBrush = RGB(0, 0, 255);
}

void CMiniPPTView::OnUpdateShapeBrushred(CCmdUI* pCmdUI)
{
	if (m_cBrush == RGB(255, 0, 0)) {
	pCmdUI->SetRadio(1);

	}
	else {
		pCmdUI->SetRadio(0);
	}
}

void CMiniPPTView::OnUpdateShapeBrushgreen(CCmdUI* pCmdUI)
{
	if (m_cBrush == RGB(0, 255, 0)) {
		pCmdUI->SetRadio(1);

	}
	else {
		pCmdUI->SetRadio(0);
	}
}

void CMiniPPTView::OnUpdateShapeBrushblue(CCmdUI* pCmdUI)
{
	if (m_cBrush == RGB(0, 0, 255)) {
		pCmdUI->SetRadio(1);

	}
	else {
		pCmdUI->SetRadio(0);
	}
}
