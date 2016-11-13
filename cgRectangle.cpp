// cgRectangle.cpp: implementation of the cgRectangle class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "GraphicsEditor.h"
#include "cgRectangle.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

cgRectangle::cgRectangle()
{
	m_bFirstPoint = false;
	m_fWidth = 1.0f;
}

cgRectangle::~cgRectangle()
{

}

void cgRectangle::Darw()
{
	float x0,y0,x1,y1;
	//���ƾ���
	x0 = m_point1.m_fX;
	x1 = m_point2.m_fX;
	y0 = m_point1.m_fY;
	y1 = m_point2.m_fY;
	glLineWidth(m_fWidth);
	glColor3f(0.5,0,1);
	glBegin(GL_LINE_LOOP);
		glVertex2f(x0,y0);
		glVertex2f(x1,y0);
		glVertex2f(x1,y1);
		glVertex2f(x0,y1);
	glEnd();
}

BOOL cgRectangle::HitTest(float x, float y)
{
	if((x-m_point1.m_fX)*(x-m_point2.m_fX)<=0 &&
		(y-m_point1.m_fY)*(y-m_point2.m_fY)<=0)
		return true;
	return false;
}

void cgRectangle::OnLButtonDown(UINT nFlags, CPoint point)
{
	if (m_eStatus == Inputing)
	{
		if (!m_bFirstPoint) //��һ����
		{
			m_bFirstPoint = true;
			m_point2.m_fX = m_point1.m_fX = point.x;
			m_point2.m_fY = m_point1.m_fY = point.y;
		}
		else//�ڶ�����
		{
			m_point2.m_fX = point.x;
			m_point2.m_fY = point.y;

			m_bFirstPoint = false;//��ѡȡ���
			m_eStatus = InputingEnd;//�������
		}
	}
}

void cgRectangle::OnMouseMove(UINT nFlags, CPoint point)
{
	
	if (m_bFirstPoint && m_eStatus == Inputing)//��2�ΰ���
	{
		m_point2.m_fX = point.x;
		m_point2.m_fY = point.y;
	}

	if (nFlags == MK_LBUTTON  && m_eStatus == Selected)//�ƶ�ͼ��
	{
		m_eStatus = Moving;
		m_tempPoint = point;
	}
	if (nFlags == MK_LBUTTON  && m_eStatus == Moving)//�ƶ�ͼ��
	{
		int dx = point.x -  m_tempPoint.x;
		int dy = point.y -  m_tempPoint.y;

		m_point1.m_fX += dx; m_point1.m_fY -= dy;
		m_point2.m_fX += dx; m_point2.m_fY -= dy;

		m_tempPoint = point;
	}
}

void cgRectangle::CalBox()
{

}

void cgRectangle::OnRButtonDown(UINT nFlags, CPoint point)
{

}
