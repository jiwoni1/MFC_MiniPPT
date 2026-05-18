#include "pch.h"
#include "CMyShape.h"

CMyShape::CMyShape() {

}

CMyShape::~CMyShape() {

}


bool CMyShape::PtInShape(CPoint point)
{
	// 좌표가 도형에 포함됬는지 여부
	if (m_point.x <= point.x && point.x <= m_point.x + m_size.cx &&
		m_point.y <= point.y && point.y <= m_point.y + m_size.cy
		) {
		return TRUE;
	}

	return false;
}
