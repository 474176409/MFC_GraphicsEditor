// cgLine.cpp: implementation of the cgLine class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "GraphicsEditor.h"
#include "cgLine.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

cgLine::cgLine()
{
	m_fWidth = 1.0f;

	m_bFirstPoint = FALSE;
}

cgLine:: cgLine(cgPoint p1,cgPoint p2)
{
	m_ptP1 = p1;
	m_ptP2 = p2;
}

cgLine::~cgLine()
{

}

void cgLine::Darw()
{
	glLineWidth(m_fWidth);
	glColor3f(0,0.4,0.6);
	glBegin(GL_LINES);
		glVertex2f(m_ptP1.m_fX,m_ptP1.m_fY);
		//glVertex2f(m_ptP1.m_fX,m_ptP1.m_fY);
		glVertex2f(m_ptP2.m_fX,m_ptP2.m_fY);
	glEnd();

	if (m_eStatus == Selected || m_eStatus == Moving)
	{
		float x0,y0,x1,y1;

		//������Χ����
		x0 = m_ptP1.m_fX;x1 = m_ptP2.m_fX;
		if (x0 > m_ptP2.m_fX) 
		{
			x0 = m_ptP2.m_fX; x1 = m_ptP1.m_fX; 
		}
		y0 = m_ptP1.m_fY;y1 = m_ptP2.m_fY;
		if (y0 > m_ptP2.m_fY) 
		{
			y0 = m_ptP2.m_fY; y1 = m_ptP1.m_fY; 
		}
		if(m_ptP1.m_fX == m_ptP2.m_fX)
		{
			x0 = m_ptP1.m_fX - 2;
			x1 = m_ptP1.m_fX + 2;
		}
		else if(m_ptP1.m_fY == m_ptP2.m_fY)
		{
			y0 = m_ptP1.m_fY - 2;
			y1 = m_ptP1.m_fY + 2;
		}

		//���ƾ���
		glColor3f(0,1,0);
		glBegin(GL_LINE_LOOP);
			glVertex2f(x0,y0);
			glVertex2f(x1,y0);
			glVertex2f(x1,y1);
			glVertex2f(x0,y1);
		glEnd();
	}
}

void cgLine::OnLButtonDown(UINT nFlags, CPoint point)
{
	if (m_eStatus == Inputing)
	{
		if (!m_bFirstPoint) //��һ����
		{
			m_bFirstPoint = true;
			m_ptP2.m_fX = m_ptP1.m_fX = point.x;
			m_ptP2.m_fY = m_ptP1.m_fY = point.y;
		}
		else//�ڶ�����
		{
			m_ptP2.m_fX = point.x;
			m_ptP2.m_fY = point.y;

			m_bFirstPoint = false;//��ѡȡ���
			m_eStatus = InputingEnd;//�������
		}
	}
}

void cgLine::OnMouseMove(UINT nFlags, CPoint point)
{
	if (m_bFirstPoint && m_eStatus == Inputing)//��2�ΰ���
	{
		m_ptP2.m_fX = point.x;
		m_ptP2.m_fY = point.y;
	}

	if (nFlags == MK_LBUTTON  && m_eStatus == Selected)//�ƶ�ͼ��
	{
		/*int dx = point.x -  m_tempPoint.x;
		int dy = point.y -  m_tempPoint.y;

		m_ptP1.m_fX += dx; m_ptP1.m_fY -= dy;
		m_ptP2.m_fX += dx; m_ptP2.m_fY -= dy;*/

		m_eStatus = Moving;
		m_tempPoint = point;
	}
	if (nFlags == MK_LBUTTON  && m_eStatus == Moving)//�ƶ�ͼ��
	{
		int dx = point.x -  m_tempPoint.x;
		int dy = point.y -  m_tempPoint.y;

		m_ptP1.m_fX += dx; m_ptP1.m_fY -= dy;
		m_ptP2.m_fX += dx; m_ptP2.m_fY -= dy;

		m_tempPoint = point;
	}
}

BOOL cgLine::IntersectLine(cgPoint p1, cgPoint p2, cgPoint& p)
{
	float delta = (m_ptP2.m_fX - m_ptP1.m_fX) * (-(p2.m_fY -  p1.m_fY)) - (m_ptP2.m_fY - m_ptP1.m_fY) * (-(p2.m_fX -  p1.m_fX));

	if (fabs(delta) < 0.01f) //ƽ��
	{
		return FALSE;//��Ҫ��һ�������غ����
	}
	else
	{
		float t = ((p1.m_fX - m_ptP1.m_fX) * (-(p2.m_fY -  p1.m_fY)) - (p1.m_fY - m_ptP1.m_fY) * (-(p2.m_fX -  p1.m_fX))) / delta;

		float s = ((m_ptP2.m_fX - m_ptP1.m_fX) * (p1.m_fY -  m_ptP1.m_fY) + (m_ptP2.m_fY - m_ptP1.m_fY) * (m_ptP1.m_fX -  p1.m_fX)) / delta;

		if (t>= -0.01f && t<=1.01f && s >= -0.01f && s<=1.01f)
		{
			p.m_fX = m_ptP1.m_fX + (m_ptP2.m_fX -  m_ptP1.m_fX) * t;
			p.m_fY = m_ptP1.m_fY + (m_ptP2.m_fY -  m_ptP1.m_fY) * t;

			return TRUE; 
		}
	}

	return FALSE;
}

BOOL cgLine::HitTest(float x, float y)
{

	float d = 2.0f;//��������2�������ڣ�������ڵ���1
	
	cgPoint p1,p2,p;

	//�γɾ��ε�4���ߣ��ֱ�����Ƿ��ཻ
	p1.m_fX = x-d; 	p2.m_fX = x+d; 
	p1.m_fY = p2.m_fY = y - d;
	if (IntersectLine(p1, p2, p)) return TRUE;

	p1.m_fY = p2.m_fY = y + d;
	if (IntersectLine(p1, p2, p)) return TRUE;

	p1.m_fY = y-d; 	p2.m_fY = y+d; 
	p1.m_fX = p2.m_fX = x - d;
	if (IntersectLine(p1, p2, p)) return TRUE;

	p1.m_fX = p2.m_fX = x + d;
	if (IntersectLine(p1, p2, p)) return TRUE;

	return FALSE;
}

void cgLine::CalBox()
{
	
}

void cgLine::OnRButtonDown(UINT nFlags, CPoint point)
{

}
