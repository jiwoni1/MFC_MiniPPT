
// MiniPPTView.h: CMiniPPTView 클래스의 인터페이스
//

#pragma once

// 전방 선언
class CMyShape;


class CMiniPPTView : public CView
{
protected: // serialization에서만 만들어집니다.
	CMiniPPTView() noexcept;
	DECLARE_DYNCREATE(CMiniPPTView)

// 특성입니다.
public:
	CMiniPPTDoc* GetDocument() const;

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
	virtual ~CMiniPPTView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	BOOL m_bDrag = FALSE;
	BOOL m_bDraw = FALSE;

	CPoint m_ptBegin;  // 시작 지점
	CPoint m_ptEnd;  // 끝나는 지점

	CPtrList m_listShape;

	// 선택된 색상
	COLORREF m_cBrush = RGB(255, 0, 0);

// 생성된 메시지 맵 함수
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMove(int x, int y);
	CMyShape* PtInShapes(CPoint point);
	void ReleaseList();
	afx_msg void OnDestroy();
	afx_msg void OnShapeBrushred();
	afx_msg void OnShapeBrushgreen();
	afx_msg void OnShapeBrushblue();
	afx_msg void OnUpdateShapeBrushred(CCmdUI* pCmdUI);
	afx_msg void OnUpdateShapeBrushgreen(CCmdUI* pCmdUI);
	afx_msg void OnUpdateShapeBrushblue(CCmdUI* pCmdUI);
	afx_msg void OnMyfileLoad();
	afx_msg void OnMyfileSave();
};

#ifndef _DEBUG  // MiniPPTView.cpp의 디버그 버전
inline CMiniPPTDoc* CMiniPPTView::GetDocument() const
   { return reinterpret_cast<CMiniPPTDoc*>(m_pDocument); }
#endif

