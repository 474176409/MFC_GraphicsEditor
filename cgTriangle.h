// cgTriangle.h: interface for the cgTriangle class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CGTRIANGLE_H__AFDE27A6_1844_44C9_B87B_FB6B9C0AEB44__INCLUDED_)
#define AFX_CGTRIANGLE_H__AFDE27A6_1844_44C9_B87B_FB6B9C0AEB44__INCLUDED_

#include "cgPoint.h"	// Added by ClassView
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "cgObject.h"

class cgTriangle : public cgObject  
{
public:
	void OnRButtonDown(UINT nFlags, CPoint point);
	BOOL IsInTriangle(cgPoint A, cgPoint B, cgPoint C, cgPoint D);
	float GetTriangleSquar(cgPoint p0,cgPoint p1,cgPoint p2);
	//---------------三角形的三个点-------------------//
	cgPoint m_point3;
	cgPoint m_point2;
	cgPoint m_point1;
	//------------------------------------------------//
	BOOL  m_bFirstPoint;//是否是第一个点
	BOOL  m_bSecondPoint;//是否是第二个点
	CPoint m_tempPoint;//临时变量，存贮鼠标点击位置值
	float m_size;//宽度
	void OnMouseMove(UINT nFlags, CPoint point);//响应鼠标移动的函数
	void OnLButtonDown(UINT nFlags, CPoint point);//响应左键的函数
	BOOL HitTest(float x, float y);//检测鼠标是否选中了三角形
	void Darw();//画图函数
	void CalBox();//不知道
	cgTriangle();//构造函数
	virtual ~cgTriangle();//析构函数

};

#endif // !defined(AFX_CGTRIANGLE_H__AFDE27A6_1844_44C9_B87B_FB6B9C0AEB44__INCLUDED_)
