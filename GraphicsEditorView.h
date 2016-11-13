// GraphicsEditorView.h : interface of the CGraphicsEditorView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_GRAPHICSEDITORVIEW_H__80EC695D_6C9F_4CFF_8A58_81B1927EE271__INCLUDED_)
#define AFX_GRAPHICSEDITORVIEW_H__80EC695D_6C9F_4CFF_8A58_81B1927EE271__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <gl/gl.h>
#include <gl/glu.h>
#include <gl/glaux.h>


#include "cgObject.h"
#include "cgCommandManager.h"
#include <vector> //ÈÝÆ÷
using namespace std;


class CGraphicsEditorView : public CView
{
protected: // create from serialization only
	CGraphicsEditorView();
	DECLARE_DYNCREATE(CGraphicsEditorView)

// Attributes
public:
	CGraphicsEditorDoc* GetDocument();

	HGLRC m_hRC; //Rendering Context
    CDC* m_pDC; //Device Context  
	BOOL InitializeOpenGL ();
	BOOL SetupPixelFormat();
	void  RenderScene();

	int m_iWindowWidth;
	int m_iWindowHeight;
	cgCommandManager  m_cgComandManager;

	vector<cgObject*> m_cgEntitys;
	void SetEntitysStatus(cgEntityStatus) ;
	cgObject*         m_cgCurrentEntity;
	cgObject*         m_cgSelectEntity;
// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGraphicsEditorView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CGraphicsEditorView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CGraphicsEditorView)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnButtonLine();
	afx_msg void OnUpdateButtonLine(CCmdUI* pCmdUI);
	afx_msg void OnUpdateButtonPoint(CCmdUI* pCmdUI);
	afx_msg void OnButtonPoint();
	afx_msg void OnButtonTriangle();
	afx_msg void OnUpdateButtonTriangle(CCmdUI* pCmdUI);
	afx_msg void OnButtonRectangle();
	afx_msg void OnUpdateButtonRectangle(CCmdUI* pCmdUI);
	afx_msg void OnButtonPolygon();
	afx_msg void OnUpdateButtonPolygon(CCmdUI* pCmdUI);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnButtonBackline();
	afx_msg void OnUpdateButtonBackline(CCmdUI* pCmdUI);
	afx_msg void OnButtonCircle();
	afx_msg void OnUpdateButtonCircle(CCmdUI* pCmdUI);
	afx_msg void OnButtonB();
	afx_msg void OnUpdateButtonB(CCmdUI* pCmdUI);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	afx_msg void OnEditColor();
	afx_msg void OnUpdateEditColor(CCmdUI* pCmdUI);
	afx_msg void OnUndo();
	afx_msg void OnUpdateUndo(CCmdUI* pCmdUI);
	afx_msg void OnRedo();
	afx_msg void OnUpdateRedo(CCmdUI* pCmdUI);
	afx_msg void OnEditCut();
	afx_msg void OnUpdateEditCut(CCmdUI* pCmdUI);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in GraphicsEditorView.cpp
inline CGraphicsEditorDoc* CGraphicsEditorView::GetDocument()
   { return (CGraphicsEditorDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GRAPHICSEDITORVIEW_H__80EC695D_6C9F_4CFF_8A58_81B1927EE271__INCLUDED_)
