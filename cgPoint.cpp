// cgPoint.cpp: implementation of the cgPoint class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "GraphicsEditor.h"
#include "cgPoint.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

cgPoint::cgPoint()
{
	m_fX = 0.0f;
	m_fY = 0.0f;

	m_fSize = 5.0f;

	m_eStatus = Drawing;
}

cgPoint::cgPoint(float x,float y)
{
	m_fX = x;
	m_fY = y;
}

cgPoint::~cgPoint()
{

}

void cgPoint::SetPointSize(float size)
{
	m_fSize = size;
}

void cgPoint::Darw()
{
	glPointSize(m_fSize);
	glColor3f(m_fR,m_fG,m_fB);
	glBegin(GL_POINTS);
		glVertex2f(m_fX,m_fY);
	glEnd();
}

void cgPoint::OnLButtonDown(UINT nFlags, CPoint point)
{
	if (m_eStatus == Inputing)
	{
		m_fX = (float)point.x;
		m_fY = (float)point.y;
		m_eStatus = InputingEnd;
	}
}

void cgPoint::OnMouseMove(UINT nFlags, CPoint point)
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

		m_fX += dx; m_fY -= dy;
		m_tempPoint = point;
	}
}

BOOL cgPoint::HitTest(float x, float y)
{
	float d = m_fSize + 1.0f;

	float dx = (float)fabs(x - m_fX);
	float dy = (float)fabs(y - m_fY);

	if (dx<=d && dy<=d) return TRUE;

	return FALSE;
}

void cgPoint::CalBox()
{

}