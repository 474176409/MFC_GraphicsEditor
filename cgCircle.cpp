// cgCircle.cpp: implementation of the cgCircle class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "GraphicsEditor.h"
#include "cgCircle.h"
#include "cgPoint.h"
#include "math.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

cgCircle::cgCircle()
{
	R=0;
	m_first=false;
}

cgCircle::~cgCircle()
{

}

void cgCircle::Darw()
{
	int i=0;
	int n=100;
	float x=(x1+x2)/2.0;
	float y=(y1+y2)/2.0;
	R=sqrt((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2))/2;
	glColor3f(1,0,0);
	glBegin(GL_LINE_LOOP);
     for(i=0; i<n; ++i)
         glVertex2f(x+R*cos(2*3.1415926/n*i), y+R*sin(2*3.1415926/n*i));
     glEnd();
	 //画矩形
	if (m_eStatus == Selected || m_eStatus == Moving)
	{
		//绘制矩形
		glColor3f(0,1,0);
		glBegin(GL_LINE_LOOP);
			glVertex2f(x+R,y+R);
			glVertex2f(x+R,y-R);
			glVertex2f(x-R,y-R);
			glVertex2f(x-R,y+R);
		glEnd();
	}
}

void cgCircle::CalBox()
{

}

BOOL cgCircle::HitTest(float x, float y)
{
	float x0=(x1+x2)/2.0;
	float y0=(y1+y2)/2.0;
	if(sqrt((x-x0)*(x-x0)+(y-y0)*(y-y0))<R)
		return true;
	return false;
}

void cgCircle::OnLButtonDown(UINT nFlags, CPoint point)
{
	if(!m_first)
	{
		x1=point.x;
		y1=point.y;
		m_first=true;
	}
	else
	{
		x2=point.x;
		y2=point.y;
		m_eStatus = InputingEnd;
	}
}

void cgCircle::OnMouseMove(UINT nFlags, CPoint point)
{
	if(m_first && m_eStatus == Inputing)
	{
		x2=point.x;
		y2=point.y;
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

		x1 += dx; y1 -= dy;
		x2 += dx; y2 -= dy;

		m_tempPoint = point;
	}
}

void cgCircle::OnRButtonDown(UINT nFlags, CPoint point)
{

}
