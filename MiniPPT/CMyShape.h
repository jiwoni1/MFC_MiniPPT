#pragma once

// 상속
// memory leak이 나는걸 확인하고 싶으면, CObject를 상속받게 해주면 됨
class CMyShape : public CObject
{
public:
	CMyShape();
	~CMyShape();

	struct MYSHAPE {
		int x;
		int y;
		int cx;
		int cy;

		COLORREF cbrush;
	};


	CPoint m_point;
	CSize m_size;
	COLORREF m_cBrush = RGB(0, 0, 210);
	COLORREF m_cPen = RGB(0, 50, 75);
	int m_nPenWidth = 3;
	bool PtInShape(CPoint point);
	MYSHAPE GetData();
};

