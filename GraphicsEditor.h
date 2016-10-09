// GraphicsEditor.h : main header file for the GRAPHICSEDITOR application
//

#if !defined(AFX_GRAPHICSEDITOR_H__F75F8D32_E592_4CB2_88BF_9E10006A6823__INCLUDED_)
#define AFX_GRAPHICSEDITOR_H__F75F8D32_E592_4CB2_88BF_9E10006A6823__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CGraphicsEditorApp:
// See GraphicsEditor.cpp for the implementation of this class
//

class CGraphicsEditorApp : public CWinApp
{
public:
	CGraphicsEditorApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGraphicsEditorApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CGraphicsEditorApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GRAPHICSEDITOR_H__F75F8D32_E592_4CB2_88BF_9E10006A6823__INCLUDED_)
