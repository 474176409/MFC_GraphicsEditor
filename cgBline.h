// cgBline.h: interface for the cgBline class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CGBLINE_H__FB783D1D_4FCA_458D_A9B2_D57D8DC364E6__INCLUDED_)
#define AFX_CGBLINE_H__FB783D1D_4FCA_458D_A9B2_D57D8DC364E6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "cgObject.h"
#include "cgPoint.h"

class cgBline : public cgObject  
{
public:
	int count;
	cgPoint drawBezier(cgPoint A, cgPoint B, cgPoint C, cgPoint D,float t);
	void drawLine(cgPoint p1, cgPoint p2);
	void drawDot(cgPoint pt);
	void Darw();
	void OnLButtonDown(UINT nFlags, CPoint point);
	void OnMouseMove(UINT nFlags, CPoint point);
	BOOL HitTest(float x, float y);
	void CalBox();
	void OnRButtonDown(UINT nFlags, CPoint point);
	cgBline();
	virtual ~cgBline();

	CPoint m_tempPoint;//临时变量，存贮鼠标点击位置值
	cgPoint m_points[4];//三次B曲线

	float max_x,max_y;
	float min_x,min_y;
	
};

#endif // !defined(AFX_CGBLINE_H__FB783D1D_4FCA_458D_A9B2_D57D8DC364E6__INCLUDED_)
