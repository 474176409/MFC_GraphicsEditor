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
	//==============�������===================//
	float m_fX;
	float m_fY;
	//=========================================//
	CPoint m_tempPoint;//��ʱ���������������λ��ֵ
	void SetPointSize(float size);//���õ�Ĵ�С

	void Darw();//����
	void OnLButtonDown(UINT nFlags, CPoint point);
	void OnMouseMove(UINT nFlags, CPoint point);
	BOOL HitTest(float x, float y);
	void CalBox();

private:
	float m_fSize;//��Ĵ�С
};

#endif // !defined(AFX_CGPOINT_H__976BD827_7D73_4558_A012_306856910F4A__INCLUDED_)
