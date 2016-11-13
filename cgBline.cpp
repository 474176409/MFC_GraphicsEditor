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
	PointSort = 0;//记录点的个数
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
	float d = 2.0f;//左右上下2个像素内，必须大于等于1

	CPoint p1, p2, p;

	//形成矩形的4条边，分别计算是否相交
	p1.x = x - d; 	p2.x = x + d;
	p1.y = p2.y = y - d;
	if (IntersectLine(p1, p2, p)) return TRUE;

	p1.y = p2.y = y + d;
	if (IntersectLine(p1, p2, p)) return TRUE;

	p1.y = y - d; 	p2.y = y + d;
	p1.x = p2.x = x - d;
	if (IntersectLine(p1, p2, p)) return TRUE;

	p1.x = p2.x = x + d;
	if (IntersectLine(p1, p2, p)) return TRUE;

	return FALSE;
}

void cgBline::OnMouseMove(UINT nFlags, CPoint point)
{
if (PointSort == 1 && m_eStatus == Inputing)//第2次按键
	{
		tmp = point;
	}

	if (nFlags == MK_LBUTTON  && m_eStatus == Selected)//移动图形
	{
		m_eStatus = Moving;
		m_tempPoint = point;
	}
	if (nFlags == MK_LBUTTON  && m_eStatus == Moving)//移动图形
	{
		int dx = point.x - m_tempPoint.x;
		int dy = point.y - m_tempPoint.y;

		for (int i = 0; i < bLine.size(); i++)
		{
			bLine.at(i).x += dx;
			bLine.at(i).y -= dy;
		}
		tmp.x += dx;
		tmp.y -= dy;
		m_tempPoint = point;
	}
}

void cgBline::OnLButtonDown(UINT nFlags, CPoint point)
{
if (m_eStatus == Inputing)
	{
		if (PointSort == 0)
		{
			PointSort++;
			bLine.push_back(point);
		}
		else if (PointSort == 1)
		{
			if (fabs(bLine.back().x - point.x) <= 2 && fabs(bLine.back().y - point.y) <= 2)
			{
				tmp = bLine.back();
				m_eStatus = InputingEnd;
			}
			else
			{
				bLine.push_back(point);
			}
		}
	}
}

void cgBline::Darw()
{
	int i;
	sol1();
	sol4();

	if (PointSort >= 1 && m_eStatus == Selected || m_eStatus == Moving)
	{
		float x0, x1, y0, y1;
		x0 = x1 = bLine.at(0).x;
		y0 = y1 = bLine.at(0).y;
		//计算外围矩形
		int i;
		for (i = 1; i < bLine.size(); i++)
		{
			if (bLine.at(i).x > x0)
			{
				x0 = bLine.at(i).x;
			}
			if (bLine.at(i).x < x1)
			{
				x1 = bLine.at(i).x;
			}
			if (bLine.at(i).y > y0)
			{
				y0 = bLine.at(i).y;
			}
			if (bLine.at(i).y < y1)
			{
				y1 = bLine.at(i).y;
			}
		}
		if (x0 == x1)
		{
			x0 -= 2;
			x1 += 2;
		}
		if (y0 == y1)
		{
			y0 -= 2;
			y1 += 2;
		}

		//绘制矩形
		glColor3f(0, 1, 0);
		glBegin(GL_LINE_LOOP);
		glVertex2f(x0, y0);
		glVertex2f(x1, y0);
		glVertex2f(x1, y1);
		glVertex2f(x0, y1);
		glEnd();
	}
}


void cgBline::sol1()//控制多变形的轮廓
{
	int i;
	glLineWidth(1);
	glColor3f(0, 0, 1);
	glBegin(GL_LINES);
	if (bLine.size() >= 2)
	{
		for (i = 0; i < bLine.size() - 1; i++)
		{
			glVertex2f(bLine.at(i).x, bLine.at(i).y);
			glVertex2f(bLine.at(i + 1).x, bLine.at(i + 1).y);
		}
	}
	glFlush();
	glEnd();
}

double cgBline::sol2(int nn, int k)//计算多项式的系数
{
	int i;
	double sum = 1;
	for (i = 1; i <= nn; i++)
		sum *= i;
	for (i = 1; i <= k; i++)
		sum /= i;
	for (i = 1; i <= nn - k; i++)
		sum /= i;
	return sum;
}

void cgBline::sol3(double t)//计算Bezier曲线上点的坐标
{
	double x = 0, y = 0, Ber;
	int k, n = bLine.size();
	for (k = 0; k< n; k++)
	{
		Ber = sol2(n - 1, k)*pow(t, k)*pow(1 - t, n - 1 - k);
		x += bLine.at(k).x*Ber;
		y += bLine.at(k).y*Ber;
	}
	//glLineWidth(m_fWidth);
	glColor3f(m_fR, m_fG, m_fB);
	glBegin(GL_POINTS);
	glVertex2f(x, y);
	glFlush();
	glEnd();

}

void cgBline::sol4()//根据控制点，求曲线上的m个点  
{
	int m = 5000, i;
	for (i = 0; i <= m; i++)
		sol3((double)i / (double)m);
}

BOOL cgBline::IntersectLine(CPoint p1, CPoint p2, CPoint &p)
{
for (int i = 0; i < bLine.size() - 1; i++)
	{
		CPoint point1 = bLine.at(i);
		CPoint point2 = bLine.at(i + 1);
		float delta = (point2.x - point1.x) * (-(p2.y - p1.y)) - (point2.y - point1.y) * (-(p2.x - p1.x));
		if (fabs(delta) < 0.01f) //平行
		{
			return FALSE;//需要进一步考虑重合情况
		}
		else
		{
			float t = ((p1.x - point1.x) * (-(p2.y - p1.y)) - (p1.y - point1.y) * (-(p2.x - p1.x))) / delta;
			float s = ((point2.x - point1.x) * (p1.y - point1.y) + (point2.y - point1.y) * (point1.x - p1.x)) / delta;
			if (t >= -0.01f && t <= 1.01f && s >= -0.01f && s <= 1.01f)
			{
				p.x = point1.x + (point2.x - point1.x) * t;
				p.y = point1.y + (point2.y - point1.y) * t;
				return TRUE;
			}
		}
	}
	return FALSE;
}
