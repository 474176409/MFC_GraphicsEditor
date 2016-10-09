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
	//---------------�����ε�������-------------------//
	cgPoint m_point3;
	cgPoint m_point2;
	cgPoint m_point1;
	//------------------------------------------------//
	BOOL  m_bFirstPoint;//�Ƿ��ǵ�һ����
	BOOL  m_bSecondPoint;//�Ƿ��ǵڶ�����
	CPoint m_tempPoint;//��ʱ���������������λ��ֵ
	float m_size;//���
	void OnMouseMove(UINT nFlags, CPoint point);//��Ӧ����ƶ��ĺ���
	void OnLButtonDown(UINT nFlags, CPoint point);//��Ӧ����ĺ���
	BOOL HitTest(float x, float y);//�������Ƿ�ѡ����������
	void Darw();//��ͼ����
	void CalBox();//��֪��
	cgTriangle();//���캯��
	virtual ~cgTriangle();//��������

};

#endif // !defined(AFX_CGTRIANGLE_H__AFDE27A6_1844_44C9_B87B_FB6B9C0AEB44__INCLUDED_)
