// cgPoint.h: interface for the cgPoint class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CGPOINT_H__976BD827_7D73_4558_A012_306856910F4A__INCLUDED_)
#define AFX_CGPOINT_H__976BD827_7D73_4558_A012_306856910F4A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "cgObject.h"

class cgPoint : public cgObject  
{
public:
	cgPoint();
	cgPoint(float x,float y);
	virtual ~cgPoint();
	//==============点的坐标===================//
	float m_fX;
	float m_fY;
	//=========================================//
	CPoint m_tempPoint;//临时变量，存贮鼠标点击位置值
	void SetPointSize(float size);//设置点的大小

	void Darw();//画点
	void OnLButtonDown(UINT nFlags, CPoint point);
	void OnMouseMove(UINT nFlags, CPoint point);
	BOOL HitTest(float x, float y);
	void CalBox();

private:
	float m_fSize;//点的大小
};

#endif // !defined(AFX_CGPOINT_H__976BD827_7D73_4558_A012_306856910F4A__INCLUDED_)
