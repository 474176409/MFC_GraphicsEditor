// cgBline.cpp: implementation of the cgBline class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "GraphicsEditor.h"
#include "cgBline.h"
#include "cgPoint.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

cgBline::cgBline()
{
	count=0;//记录点的个数
}

cgBline::~cgBline()
{

}

void cgBline::OnRButtonDown(UINT nFlags, CPoint point)
{
}

void cgBline::CalBox()
{

}

BOOL cgBline::HitTest(float x, float y)
{
	if(x<=max_x&&x>=min_x&&y<=max_y&&y>=min_y)
		return true;
	return false;
}

void cgBline::OnMouseMove(UINT nFlags, CPoint point)
{
	if (nFlags == MK_LBUTTON  && m_eStatus == Selected)//移动图形
	{
		m_eStatus = Moving;
		m_tempPoint = point;
	}
	if (nFlags == MK_LBUTTON  && m_eStatus == Moving)//移动图形
	{
		int dx = point.x -  m_tempPoint.x;
		int dy = point.y -  m_tempPoint.y;
		for(int i=0;i<count;i++)
		{
			m_points[i].m_fX += dx;
			m_points[i].m_fY -= dy;
		}

		m_tempPoint = point;
	}
}

void cgBline::OnLButtonDown(UINT nFlags, CPoint point)
{
	if(m_eStatus == Inputing)
	{
		m_points[count++]=cgPoint(point.x,point.y);
		if(count>=4)
		{m_eStatus = InputingEnd;return ;}
	}
}

void cgBline::Darw()
{
	int i;
	if(count>=4)
	{
		drawDot(m_points[0]);    
		drawDot(m_points[1]);    
		drawDot(m_points[2]);    
		drawDot(m_points[3]);    
		glColor3f(1.0, 1.0, 0.0);    
		drawLine(m_points[0], m_points[1]);    
		drawLine(m_points[1], m_points[2]);    
		drawLine(m_points[2], m_points[3]);    
		glColor3f(0.0, 1.0, 1.0);    
		cgPoint POld = m_points[0];    
		for (float t = 0.0; t<=1.0;t+=0.01f)    
		{    
			 cgPoint P = drawBezier(m_points[0], m_points[1], m_points[2],  m_points[3], t);    
			 drawLine(POld, P);    
			 POld = P;    
		} 
	}
	
	//算边界
	max_x=m_points[0].m_fX,max_y=m_points[0].m_fY;
	min_x=m_points[0].m_fX,min_y=m_points[0].m_fY;
	for(i=0;i<count;i++)
	{
		if(m_points[i].m_fX>max_x)
			max_x=m_points[i].m_fX;
		if(m_points[i].m_fX<min_x)
			min_x=m_points[i].m_fX;
	}
	for(i=0;i<count;i++)
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

void cgBline::drawDot(cgPoint pt)
{
	glBegin(GL_POINTS);    
    glVertex2f(pt.m_fX, pt.m_fY);    
	glEnd();     
}

void cgBline::drawLine(cgPoint p1, cgPoint p2)
{
	glBegin(GL_LINES);    
    glVertex2f(p1.m_fX, p1.m_fY);    
    glVertex2f(p2.m_fX, p2.m_fY);    
    glEnd();    
}

cgPoint cgBline::drawBezier(cgPoint A, cgPoint B, cgPoint C, cgPoint D, float t)
{
	cgPoint P;  
    float a1 = pow((1-t),3);  
    float a2 = pow((1-t),2)*3*t;  
    float a3 = 3*t*t*(1-t);  
    float a4 = t*t*t;  
  
    P.m_fX = a1*A.m_fX+a2*B.m_fX+a3*C.m_fX+a4*D.m_fX;  
    P.m_fY = a1*A.m_fY+a2*B.m_fY+a3*C.m_fY+a4*D.m_fY;  
    return P;    
}
