// cgTriangle.cpp: implementation of the cgTriangle class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "GraphicsEditor.h"
#include "cgTriangle.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
//构造函数，初始化一些数据
cgTriangle::cgTriangle()
{
	m_size = 1.0f;//点的大小
	m_bFirstPoint = false;//第一个点
	m_bSecondPoint = false;//第二个点
}

cgTriangle::~cgTriangle()
{

}
//这个暂时没有什么用
void cgTriangle::CalBox()
{

}

void cgTriangle::Darw()
{
	//==========绘制阶段===========//
	glLineWidth(m_size);//设置OpenGL画图时线的宽度
	glColor3f(m_fR,m_fG,m_fB);//设置OpenGL画图的线的颜色
	glBegin(GL_LINES);//划线，画三角形
		glVertex2f(m_point1.m_fX,m_point1.m_fY);
		glVertex2f(m_point2.m_fX,m_point2.m_fY);
		glVertex2f(m_point2.m_fX,m_point2.m_fY);
		glVertex2f(m_point3.m_fX,m_point3.m_fY);
		glVertex2f(m_point3.m_fX,m_point3.m_fY);
		glVertex2f(m_point1.m_fX,m_point1.m_fY);
	glEnd();
	//=============选取图形移动阶段的外围矩形===================//
	if (m_eStatus == Selected || m_eStatus == Moving)
	{
		/*
		计算外围矩形的方法是找出画的所有点的最大/最小X坐标和最大/最小Y坐标
		然后分别作为矩形的左上角和右下角
		*/
		float x0,x1,y0,y1;
		float temp;
		//最大的x,y
		temp=(m_point1.m_fX>=m_point2.m_fX) ? m_point1.m_fX : m_point2.m_fX;
		x0 = (m_point3.m_fX>=temp) ? m_point3.m_fX : temp;
		temp=(m_point1.m_fY>=m_point2.m_fY) ? m_point1.m_fY : m_point2.m_fY;
		y0 = (m_point3.m_fY>=temp) ? m_point3.m_fY : temp;
		//最小的想x,y
		temp=(m_point1.m_fX<=m_point2.m_fX) ? m_point1.m_fX : m_point2.m_fX;
		x1 = (m_point3.m_fX<=temp) ? m_point3.m_fX : temp;
		temp=(m_point1.m_fY<=m_point2.m_fY) ? m_point1.m_fY : m_point2.m_fY;
		y1 = (m_point3.m_fY<=temp) ? m_point3.m_fY : temp;

		//绘制矩形
		glColor3f(0,1,0);
		glBegin(GL_LINE_LOOP);
			glVertex2f(x0,y0);
			glVertex2f(x1,y0);
			glVertex2f(x1,y1);
			glVertex2f(x0,y1);
		glEnd();
	}
}
/*判断点是否在三角形内*/
BOOL cgTriangle::HitTest(float x, float y)
{
	cgPoint p;
	p.m_fX=x;
	p.m_fY=y;
	if(IsInTriangle(m_point1, m_point2, m_point3, p))return true;
	return false;
}
//左键响应函数
void cgTriangle::OnLButtonDown(UINT nFlags, CPoint point)
{
		if (m_eStatus == Inputing)//如果是输入状态就响应
	{
		if (!m_bFirstPoint) //第一个点
		{
			m_bFirstPoint = true;
			m_point1.m_fX = m_point2.m_fX = m_point3.m_fX = point.x;
			m_point1.m_fY = m_point2.m_fY = m_point3.m_fY = point.y;
		}
		else if(m_bFirstPoint&&!m_bSecondPoint)//第二个点
		{
			m_bSecondPoint = true;
			m_point2.m_fX = m_point3.m_fX=point.x;
			m_point2.m_fY = m_point3.m_fY=point.y;

		}
		else
		{
			m_point3.m_fX = point.x;
			m_point3.m_fY = point.y;
			m_bSecondPoint = false;
			m_bFirstPoint = false;

			m_eStatus = InputingEnd;//输入结束
		}
	}
}
//鼠标移动函数
void cgTriangle::OnMouseMove(UINT nFlags, CPoint point)
{
	//画图阶段
	if (m_bFirstPoint && !m_bSecondPoint && m_eStatus == Inputing)//第2次按键
	{
		m_point2.m_fX = point.x;
		m_point2.m_fY = point.y;
		m_point3.m_fX = point.x;
		m_point3.m_fY = point.y;
	}
	if(m_bSecondPoint && m_eStatus == Inputing)//第三次
	{
		m_point3.m_fX = point.x;
		m_point3.m_fY = point.y;
	}
	//移动阶段
	if (nFlags == MK_LBUTTON  && m_eStatus == Selected)//移动图形
	{
		m_eStatus = Moving;
		m_tempPoint = point;
	}
	if (nFlags == MK_LBUTTON  && m_eStatus == Moving)//移动图形
	{
		int dx = point.x -  m_tempPoint.x;
		int dy = point.y -  m_tempPoint.y;

		m_point1.m_fX += dx; m_point1.m_fY -= dy;
		m_point2.m_fX += dx; m_point2.m_fY -= dy;
		m_point3.m_fX += dx; m_point3.m_fY -= dy;

		m_tempPoint = point;
	}
}

//计算三角形的面积
/*
通过判断三个小三角形面积和是否等于大三角形来判断是否在三角形内部
*/
float cgTriangle::GetTriangleSquar(cgPoint p0, cgPoint p1, cgPoint p2)
{
	cgPoint AB,   BC;      
    AB.m_fX = p1.m_fX - p0.m_fX;     
    AB.m_fY = p1.m_fY - p0.m_fY;     
    BC.m_fX = p2.m_fX - p1.m_fX;     
    BC.m_fY = p2.m_fY - p1.m_fY;       
    return (float)fabs((AB.m_fX * BC.m_fY - AB.m_fY * BC.m_fX)) / 2.0f; 
}

BOOL cgTriangle::IsInTriangle(cgPoint A, cgPoint B, cgPoint C, cgPoint D)
{
	float SABC, SADB, SBDC, SADC;  
    SABC = GetTriangleSquar(A, B, C);  
    SADB = GetTriangleSquar(A, D, B);  
    SBDC = GetTriangleSquar(B, D, C);  
    SADC = GetTriangleSquar(A, D, C);  
  
    float SumSuqar = SADB + SBDC + SADC;  
  
    if (SumSuqar == SABC)  
    {  
        return true;  
    }  
    else  
    {  
        return false;  
    }  
}

void cgTriangle::OnRButtonDown(UINT nFlags, CPoint point)
{

}
