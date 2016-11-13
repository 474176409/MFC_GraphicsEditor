// GraphicsEditorDoc.h : interface of the CGraphicsEditorDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_GRAPHICSEDITORDOC_H__2B17D059_B94C_4395_9D6A_E320A6927510__INCLUDED_)
#define AFX_GRAPHICSEDITORDOC_H__2B17D059_B94C_4395_9D6A_E320A6927510__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CGraphicsEditorDoc : public CDocument
{
protected: // create from serialization only
	CGraphicsEditorDoc();
	DECLARE_DYNCREATE(CGraphicsEditorDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGraphicsEditorDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CGraphicsEditorDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CGraphicsEditorDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GRAPHICSEDITORDOC_H__2B17D059_B94C_4395_9D6A_E320A6927510__INCLUDED_)
