// cgBackLine.cpp: implementation of the cgBackLine class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "GraphicsEditor.h"
#include "cgBackLine.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

cgBackLine::cgBackLine()
{
	m_first=false;//记录是不是正在画的线
	m_count=0;//记录点的个数
}

cgBackLine::~cgBackLine()
{

}

void cgBackLine::Darw()
{
	int i=0;
	glLineWidth(1.0f);
	glColor3f(0.5,0.5,0.5);
	glBegin(GL_LINES);
		for(i=0;i<m_count-1;i++)
		{
				glVertex2f(m_points[i].m_fX,m_points[i].m_fY);
				glVertex2f(m_points[i+1].m_fX,m_points[i+1].m_fY);
		}
	glEnd();
	//处理最后一条线
	if(m_eStatus == Inputing)
	{
		glColor3f(0,1,0);
		glBegin(GL_LINES);
			glVertex2f(m_points[m_count-1].m_fX,m_points[m_count-1].m_fY);
			glVertex2f(m_lastx,m_lasty);
		glEnd();
	}
	else
	{
		glColor3f(1,1,1);
		glBegin(GL_LINES);
			glVertex2f(m_points[m_count-1].m_fX,m_points[m_count-1].m_fY);
		glEnd();
	}
	//画矩形
	max_x=m_points[0].m_fX,max_y=m_points[0].m_fY;
	min_x=m_points[0].m_fX,min_y=m_points[0].m_fY;
	for(i=0;i<m_count;i++)
	{
		if(m_points[i].m_fX>max_x)
			max_x=m_points[i].m_fX;
		if(m_points[i].m_fX<min_x)
			min_x=m_points[i].m_fX;
	}
	for(i=0;i<m_count;i++)
	{
		if(m_points[i].m_fY>max_y)
			max_y=m_points[i].m_fY;
		if(m_points[i].m_fY<min_y)
			min_y=m_points[i].m_fY;
	}
	
	if (m_eStatus == Selected || m_eStatus == Moving)
	{
		//绘制矩形
		glColor3f(0,1,0);
		glBegin(GL_LINE_LOOP);
			glVertex2f(max_x,max_y);
			glVertex2f(min_x,max_y);
			glVertex2f(min_x,min_y);
			glVertex2f(max_x,min_y);
		glEnd();
	}
}

void cgBackLine::OnLButtonDown(UINT nFlags, CPoint point)
{
	if(m_eStatus == Inputing)
	{
		if(!m_first)
		{
			m_points[m_count++]=cgPoint(point.x,point.y);
			m_firstx=point.x;
			m_firsty=point.y;
			m_first=true;return ;
		}
		else
		{
			m_points[m_count++]=cgPoint(point.x,point.y);
			m_lastx=point.x;
			m_lasty=point.y;
		}
	}
}

void cgBackLine::OnMouseMove(UINT nFlags, CPoint point)
{
	if(m_eStatus == Inputing)//当还是输入状态的时候
	{
		if (m_first) 
		{
			m_lastx = point.x, m_lasty = point.y;
		}
	}

	if (nFlags == MK_LBUTTON  && m_eStatus == Selected)//移动图形
	{
		m_eStatus = Moving;
		m_tempPoint = point;
	}
	if (nFlags == MK_LBUTTON  && m_eStatus == Moving)//移动图形
	{
		int dx = point.x -  m_tempPoint.x;
		int dy = point.y -  m_tempPoint.y;
		for(int i=0;i<m_count;i++)
		{
			m_points[i].m_fX += dx;
			m_points[i].m_fY -= dy;
		}

		m_tempPoint = point;
	}
}

BOOL cgBackLine::HitTest(float x, float y)
{
	if(x<=max_x&&x>=min_x&&y<=max_y&&y>=min_y)
		return true;
	return false;
}

void cgBackLine::CalBox()
{

}

void cgBackLine::OnRButtonDown(UINT nFlags, CPoint point)
{
	m_eStatus = InputingEnd;
	//m_points[m_count++]=cgPoint(point.x,point.y);
	//m_points[m_count++]=cgPoint(m_firstx,m_firsty);
}
