// cgRectangle.h: interface for the cgRectangle class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CGRECTANGLE_H__6CEFD3AB_2EC9_4A7D_81D0_B7EDB978516C__INCLUDED_)
#define AFX_CGRECTANGLE_H__6CEFD3AB_2EC9_4A7D_81D0_B7EDB978516C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "cgObject.h"
#include "cgPoint.h"

class cgRectangle : public cgObject  
{
public:
	void OnRButtonDown(UINT nFlags, CPoint point);
	void CalBox();
	void OnMouseMove(UINT nFlags, CPoint point);
	void OnLButtonDown(UINT nFlags, CPoint point);
	BOOL HitTest(float x, float y);
	void Darw();
	cgRectangle();
	virtual ~cgRectangle();

	//���ε����϶˵�����¶˵�
	cgPoint m_point1;
	cgPoint m_point2;
	float m_fWidth ;
	CPoint m_tempPoint;//��ʱ���������������λ��ֵ

	BOOL  m_bFirstPoint;//�Ƿ��ǵ�һ����


};

#endif // !defined(AFX_CGRECTANGLE_H__6CEFD3AB_2EC9_4A7D_81D0_B7EDB978516C__INCLUDED_)
