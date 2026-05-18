#pragma once
class CMyShape
{
public:
	CMyShape();
	~CMyShape();


	CPoint m_point;
	CSize m_size;
	COLORREF m_cBrush = RGB(0, 0, 210);
	COLORREF m_cPen = RGB(0, 50, 75);
	int m_nPenWidth = 3;
	bool PtInShape(CPoint point);
};

