// cgObject.cpp: implementation of the cgObject class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "GraphicsEditor.h"
#include "cgObject.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

cgObject::cgObject()
{
	m_fR = 1.0f;
	m_fG = 1.0f;
	m_fB = 1.0f;

}

cgObject::~cgObject()
{

}

void cgObject::SetColor(float r,float g, float b)
{
	m_fR = r;
	m_fG = g;
	m_fB = b;
}

void cgObject::OnRButtonDown(UINT nFlags, CPoint point)
{

}
