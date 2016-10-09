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
//���캯������ʼ��һЩ����
cgTriangle::cgTriangle()
{
	m_size = 1.0f;//��Ĵ�С
	m_bFirstPoint = false;//��һ����
	m_bSecondPoint = false;//�ڶ�����
}

cgTriangle::~cgTriangle()
{

}
//�����ʱû��ʲô��
void cgTriangle::CalBox()
{

}

void cgTriangle::Darw()
{
	//==========���ƽ׶�===========//
	glLineWidth(m_size);//����OpenGL��ͼʱ�ߵĿ��
	glColor3f(m_fR,m_fG,m_fB);//����OpenGL��ͼ���ߵ���ɫ
	glBegin(GL_LINES);//���ߣ���������
		glVertex2f(m_point1.m_fX,m_point1.m_fY);
		glVertex2f(m_point2.m_fX,m_point2.m_fY);
		glVertex2f(m_point2.m_fX,m_point2.m_fY);
		glVertex2f(m_point3.m_fX,m_point3.m_fY);
		glVertex2f(m_point3.m_fX,m_point3.m_fY);
		glVertex2f(m_point1.m_fX,m_point1.m_fY);
	glEnd();
	//=============ѡȡͼ���ƶ��׶ε���Χ����===================//
	if (m_eStatus == Selected || m_eStatus == Moving)
	{
		/*
		������Χ���εķ������ҳ��������е�����/��СX��������/��СY����
		Ȼ��ֱ���Ϊ���ε����ϽǺ����½�
		*/
		float x0,x1,y0,y1;
		float temp;
		//����x,y
		temp=(m_point1.m_fX>=m_point2.m_fX) ? m_point1.m_fX : m_point2.m_fX;
		x0 = (m_point3.m_fX>=temp) ? m_point3.m_fX : temp;
		temp=(m_point1.m_fY>=m_point2.m_fY) ? m_point1.m_fY : m_point2.m_fY;
		y0 = (m_point3.m_fY>=temp) ? m_point3.m_fY : temp;
		//��С����x,y
		temp=(m_point1.m_fX<=m_point2.m_fX) ? m_point1.m_fX : m_point2.m_fX;
		x1 = (m_point3.m_fX<=temp) ? m_point3.m_fX : temp;
		temp=(m_point1.m_fY<=m_point2.m_fY) ? m_point1.m_fY : m_point2.m_fY;
		y1 = (m_point3.m_fY<=temp) ? m_point3.m_fY : temp;

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
/*�жϵ��Ƿ�����������*/
BOOL cgTriangle::HitTest(float x, float y)
{
	cgPoint p;
	p.m_fX=x;
	p.m_fY=y;
	if(IsInTriangle(m_point1, m_point2, m_point3, p))return true;
	return false;
}
//�����Ӧ����
void cgTriangle::OnLButtonDown(UINT nFlags, CPoint point)
{
		if (m_eStatus == Inputing)//���������״̬����Ӧ
	{
		if (!m_bFirstPoint) //��һ����
		{
			m_bFirstPoint = true;
			m_point1.m_fX = m_point2.m_fX = m_point3.m_fX = point.x;
			m_point1.m_fY = m_point2.m_fY = m_point3.m_fY = point.y;
		}
		else if(m_bFirstPoint&&!m_bSecondPoint)//�ڶ�����
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

			m_eStatus = InputingEnd;//�������
		}
	}
}
//����ƶ�����
void cgTriangle::OnMouseMove(UINT nFlags, CPoint point)
{
	//��ͼ�׶�
	if (m_bFirstPoint && !m_bSecondPoint && m_eStatus == Inputing)//��2�ΰ���
	{
		m_point2.m_fX = point.x;
		m_point2.m_fY = point.y;
		m_point3.m_fX = point.x;
		m_point3.m_fY = point.y;
	}
	if(m_bSecondPoint && m_eStatus == Inputing)//������
	{
		m_point3.m_fX = point.x;
		m_point3.m_fY = point.y;
	}
	//�ƶ��׶�
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
		m_point3.m_fX += dx; m_point3.m_fY -= dy;

		m_tempPoint = point;
	}
}

//���������ε����
/*
ͨ���ж�����С������������Ƿ���ڴ����������ж��Ƿ����������ڲ�
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
