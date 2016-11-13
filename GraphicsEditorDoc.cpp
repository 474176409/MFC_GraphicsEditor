// GraphicsEditorDoc.cpp : implementation of the CGraphicsEditorDoc class
//

#include "stdafx.h"
#include "GraphicsEditor.h"

#include "GraphicsEditorDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CGraphicsEditorDoc

IMPLEMENT_DYNCREATE(CGraphicsEditorDoc, CDocument)

BEGIN_MESSAGE_MAP(CGraphicsEditorDoc, CDocument)
	//{{AFX_MSG_MAP(CGraphicsEditorDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGraphicsEditorDoc construction/destruction

CGraphicsEditorDoc::CGraphicsEditorDoc()
{
	// TODO: add one-time construction code here

}

CGraphicsEditorDoc::~CGraphicsEditorDoc()
{
}

BOOL CGraphicsEditorDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CGraphicsEditorDoc serialization

void CGraphicsEditorDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

/////////////////////////////////////////////////////////////////////////////
// CGraphicsEditorDoc diagnostics

#ifdef _DEBUG
void CGraphicsEditorDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CGraphicsEditorDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CGraphicsEditorDoc commands
