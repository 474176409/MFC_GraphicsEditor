// cgBackLine.h: interface for the cgBackLine class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CGBACKLINE_H__E64761C0_349F_4288_9B38_8C84EC4A50C1__INCLUDED_)
#define AFX_CGBACKLINE_H__E64761C0_349F_4288_9B38_8C84EC4A50C1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "cgObject.h"
#include "cgPoint.h"
class cgBackLine : public cgObject  
{
public:
	void OnRButtonDown(UINT nFlags, CPoint point);
	void CalBox();
	BOOL HitTest(float x, float y);
	void OnMouseMove(UINT nFlags, CPoint point);
	void OnLButtonDown(UINT nFlags, CPoint point);
	void Darw();
	cgBackLine();
	virtual ~cgBackLine();
	
	CPoint m_tempPoint;//临时变量，存贮鼠标点击位置值
	cgPoint m_points[100];//点的集合
	bool m_first;//记录是不是第一个点

	int m_count;//记录点的个数

	float m_lastx;
	float m_lasty;
	float m_firstx;
	float m_firsty;

	float max_x,max_y;
	float min_x,min_y;

};

#endif // !defined(AFX_CGBACKLINE_H__E64761C0_349F_4288_9B38_8C84EC4A50C1__INCLUDED_)
