// cgCircle.h: interface for the cgCircle class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CGCIRCLE_H__976E94D3_6855_4E3E_BC35_92195C789388__INCLUDED_)
#define AFX_CGCIRCLE_H__976E94D3_6855_4E3E_BC35_92195C789388__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "cgObject.h"

class cgCircle : public cgObject  
{
public:
	void OnRButtonDown(UINT nFlags, CPoint point);
	void OnMouseMove(UINT nFlags, CPoint point);
	void OnLButtonDown(UINT nFlags, CPoint point);
	BOOL HitTest(float x, float y);
	void CalBox();
	void Darw();
	float R;//°ë¾¶
	float x1,y1,x2,y2;//Ö±¾¶
	BOOL m_first;
	CPoint m_tempPoint;
	cgCircle();
	virtual ~cgCircle();

};

#endif // !defined(AFX_CGCIRCLE_H__976E94D3_6855_4E3E_BC35_92195C789388__INCLUDED_)
