// cgObject.h: interface for the cgObject class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CGOBJECT_H__9BABDA15_FAA8_4047_A4B4_69C11F230A5B__INCLUDED_)
#define AFX_CGOBJECT_H__9BABDA15_FAA8_4047_A4B4_69C11F230A5B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include <gl/gl.h>
#include <gl/glu.h>
#include <gl/glaux.h>
#include <math.h>

enum cgEntityStatus//枚举类型
{
   Drawing=0, Inputing,InputingEnd,Selected,Moving
};

struct cgRGB
{
	float r;
	float g;
	float b;
};

class cgObject  
{
public:
	void SetColor(float r,float g, float b);
	float GetColorR(){return m_fR;}
	float GetColorG(){return m_fG;}
	float GetColorB(){return m_fB;}

	virtual void OnRButtonDown(UINT nFlags, CPoint point);
	cgObject();
	virtual ~cgObject();
	virtual void Darw()=NULL;
	virtual void OnLButtonDown(UINT nFlags, CPoint point)=NULL;
	virtual void OnMouseMove(UINT nFlags, CPoint point) =NULL;
	virtual BOOL HitTest(float x, float y)=NULL;
	virtual void CalBox()=NULL;//计算包围盒
	//设置当前的状态
	void SetStatus(cgEntityStatus status)
	{
		m_eStatus = status;
	}
	//获取当前的状态
	cgEntityStatus GetStatus()
	{
		return m_eStatus;
	}

	cgEntityStatus m_eStatus;//当前的状态

	//包围盒
	float m_fLeft;
	float m_fBottom;
	float m_fRight;
	float m_fTop;
	//

protected:
	//点的颜色
	float m_fR;
	float m_fG;
	float m_fB;
};

#endif // !defined(AFX_CGOBJECT_H__9BABDA15_FAA8_4047_A4B4_69C11F230A5B__INCLUDED_)
