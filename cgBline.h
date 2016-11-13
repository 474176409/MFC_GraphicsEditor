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
#include "vector"
using namespace std;

class cgBline : public cgObject  
{
public:
	BOOL IntersectLine(CPoint p1, CPoint p2, CPoint& p);
	void sol4();
	void sol3(double t);
	double sol2(int nn,int k);
	void sol1();
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

	CPoint tmp;
	vector<CPoint> bLine;  //实体
	CPoint m_tempPoint;//临时变量，存贮鼠标点击位置值
	int  PointSort;
	
};

#endif // !defined(AFX_CGBLINE_H__FB783D1D_4FCA_458D_A9B2_D57D8DC364E6__INCLUDED_)
