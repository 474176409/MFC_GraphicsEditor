// cgLine.h: interface for the cgLine class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CGLINE_H__F29EBC52_3E50_4644_A4D1_72AA3D950E52__INCLUDED_)
#define AFX_CGLINE_H__F29EBC52_3E50_4644_A4D1_72AA3D950E52__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "cgObject.h"
#include "cgPoint.h"

class cgLine : public cgObject  
{
public:
    void OnRButtonDown(UINT nFlags, CPoint point);
	cgLine();//һ�㹹�캯��
	cgLine(cgPoint p1,cgPoint p2);//���εĹ��캯��
	virtual ~cgLine();
	//�߶ε������˵�
	cgPoint m_ptP1;
	cgPoint m_ptP2;
	
	CPoint m_tempPoint;//��ʱ���������������λ��ֵ

	BOOL  m_bFirstPoint;//�Ƿ��ǵ�һ����

	void Darw();//��ͼ
	void OnLButtonDown(UINT nFlags, CPoint point);
	void OnMouseMove(UINT nFlags, CPoint point);
	BOOL HitTest(float x, float y);
	void CalBox();

	BOOL IntersectLine(cgPoint p1, cgPoint p2, cgPoint& p);
private:
	float m_fWidth;

};

#endif // !defined(AFX_CGLINE_H__F29EBC52_3E50_4644_A4D1_72AA3D950E52__INCLUDED_)
