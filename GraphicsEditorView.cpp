// GraphicsEditorView.cpp : implementation of the CGraphicsEditorView class
//

#include "stdafx.h"
#include "GraphicsEditor.h"

#include "GraphicsEditorDoc.h"
#include "GraphicsEditorView.h"

#include "cgPoint.h"
#include "cgLine.h"
#include "cgTriangle.h"
#include "cgRectangle.h"
#include "cgPolygon.h"
#include "cgBackLine.h"
#include "cgCircle.h"
#include "cgBline.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CGraphicsEditorView

IMPLEMENT_DYNCREATE(CGraphicsEditorView, CView)

BEGIN_MESSAGE_MAP(CGraphicsEditorView, CView)
	//{{AFX_MSG_MAP(CGraphicsEditorView)
	ON_WM_CREATE()
	ON_WM_DESTROY()
	ON_WM_SIZE()
	ON_WM_ERASEBKGND()
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_COMMAND(ID_BUTTON_LINE, OnButtonLine)
	ON_UPDATE_COMMAND_UI(ID_BUTTON_LINE, OnUpdateButtonLine)
	ON_UPDATE_COMMAND_UI(ID_BUTTON_POINT, OnUpdateButtonPoint)
	ON_COMMAND(ID_BUTTON_POINT, OnButtonPoint)
	ON_COMMAND(ID_BUTTON_TRIANGLE, OnButtonTriangle)
	ON_UPDATE_COMMAND_UI(ID_BUTTON_TRIANGLE, OnUpdateButtonTriangle)
	ON_COMMAND(ID_BUTTON_RECTANGLE, OnButtonRectangle)
	ON_UPDATE_COMMAND_UI(ID_BUTTON_RECTANGLE, OnUpdateButtonRectangle)
	ON_COMMAND(ID_BUTTON_POLYGON, OnButtonPolygon)
	ON_UPDATE_COMMAND_UI(ID_BUTTON_POLYGON, OnUpdateButtonPolygon)
	ON_WM_RBUTTONDOWN()
	ON_COMMAND(ID_BUTTON_BACKLINE, OnButtonBackline)
	ON_UPDATE_COMMAND_UI(ID_BUTTON_BACKLINE, OnUpdateButtonBackline)
	ON_COMMAND(ID_BUTTON_CIRCLE, OnButtonCircle)
	ON_UPDATE_COMMAND_UI(ID_BUTTON_CIRCLE, OnUpdateButtonCircle)
	ON_COMMAND(ID_BUTTON_B, OnButtonB)
	ON_UPDATE_COMMAND_UI(ID_BUTTON_B, OnUpdateButtonB)
	ON_WM_CONTEXTMENU()
	ON_COMMAND(ID_EDIT_COLOR, OnEditColor)
	ON_UPDATE_COMMAND_UI(ID_EDIT_COLOR, OnUpdateEditColor)
	ON_COMMAND(ID_UNDO, OnUndo)
	ON_UPDATE_COMMAND_UI(ID_UNDO, OnUpdateUndo)
	ON_COMMAND(ID_REDO, OnRedo)
	ON_UPDATE_COMMAND_UI(ID_REDO, OnUpdateRedo)
	ON_COMMAND(ID_EDIT_CUT, OnEditCut)
	ON_UPDATE_COMMAND_UI(ID_EDIT_CUT, OnUpdateEditCut)
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGraphicsEditorView construction/destruction

CGraphicsEditorView::CGraphicsEditorView()
{
	/*cgPoint *point = new cgPoint(100.0f,200.0f);
	point->SetPointSize(5.0f);
	point->SetColor(1.0f,0.0f,0.0f);
	m_cgEntitys.push_back(point);
	point = new cgPoint(300.0f,250.0f);
	point->SetPointSize(7.0f);
	point->SetColor(1.0f,1.0f,0.0f);
	m_cgEntitys.push_back(point);

	cgLine *line = new cgLine(cgPoint(120.0f,200.0f),cgPoint(220.0f,300.0f));
	line->SetColor(0.0f,1.0f,0.0f);
	m_cgEntitys.push_back(line);

	line = new cgLine(cgPoint(200.0f,200.0f),cgPoint(300.0f,300.0f));
	line->SetColor(0.0f,1.0f,1.0f);
	m_cgEntitys.push_back(line);

	BOOL s = line->HitTest(250,250);*/

	m_cgCurrentEntity = 0;
	m_cgSelectEntity = 0;
}

CGraphicsEditorView::~CGraphicsEditorView()
{
//	while(m_cgEntitys.size())
	{
	//	m_cgEntitys.erase()
	}
}

BOOL CGraphicsEditorView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	cs.style|=WS_CLIPCHILDREN|WS_CLIPSIBLINGS;

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CGraphicsEditorView drawing

void CGraphicsEditorView::OnDraw(CDC* pDC)
{
	CGraphicsEditorDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
	// Clear out the color & depth buffers
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );	
	RenderScene(); //����Ļ�ͼ�������� RC �л���

	if (m_cgCurrentEntity) m_cgCurrentEntity->Darw();

	glFinish();

	// Now Swap the buffers
	SwapBuffers( m_pDC->GetSafeHdc() );

}

/////////////////////////////////////////////////////////////////////////////
// CGraphicsEditorView printing

BOOL CGraphicsEditorView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CGraphicsEditorView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CGraphicsEditorView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CGraphicsEditorView diagnostics

#ifdef _DEBUG
void CGraphicsEditorView::AssertValid() const
{
	CView::AssertValid();
}

void CGraphicsEditorView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CGraphicsEditorDoc* CGraphicsEditorView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CGraphicsEditorDoc)));
	return (CGraphicsEditorDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CGraphicsEditorView message handlers

int CGraphicsEditorView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	InitializeOpenGL ();
	
	return 0;
}

void CGraphicsEditorView::OnDestroy() 
{
	CView::OnDestroy();
	
	wglMakeCurrent(m_pDC->m_hDC,NULL); //�ͷ���m_hDC ��Ӧ�� RC
	wglDeleteContext(m_hRC); //ɾ�� RC if (m_pDC)
	delete m_pDC; //ɾ����ǰ View ӵ�е� DC 
}

void CGraphicsEditorView::OnSize(UINT nType, int cx, int cy) 
{
	CView::OnSize(nType, cx, cy);
	
	if ( 0 >= cx || 0 >= cy )         
		return;
	glViewport(0, 0, cx, cy); // select the full client area

      // select the projection matrix and clear it
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluOrtho2D(0, cx, 0, cy); // select the viewing volume

	// switch back to the modelview matrix and clear it
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();		

	m_iWindowWidth = cx;
	m_iWindowHeight = cy;
}

BOOL CGraphicsEditorView::OnEraseBkgnd(CDC* pDC) 
{
	// TODO: Add your message handler code here and/or call default
	
//	return CView::OnEraseBkgnd(pDC);
	return TRUE;
}

BOOL CGraphicsEditorView:: InitializeOpenGL ()
{
	  //Get a DC for the Client Area
   	    m_pDC = new CClientDC(this);
       //Failure to Get DC
  	    if(m_pDC == NULL)
   		 {
     		   MessageBox("Error Obtaining DC");
       		 return FALSE;
   		 }
        //Failure to set the pixel format
           if(!SetupPixelFormat())
   		   {
              return FALSE;
             } 
//Create Rendering Context
  	  m_hRC = wglCreateContext (m_pDC->GetSafeHdc ());
//Failure to Create Rendering Context
    if(m_hRC == 0)
    {
        MessageBox("Error Creating RC");
        return FALSE;
    }
 	     //Make the RC Current
  		  if(wglMakeCurrent (m_pDC->GetSafeHdc (), m_hRC)==FALSE)
 		   {
   		     MessageBox("Error making RC Current");
   		     return FALSE;
            } 
//Specify Black as the clear color
   	 glClearColor(0.0f,0.0f,0.0f,0.0f);

    //Specify the back of the buffer as clear depth
    	glClearDepth(1.0f);

    //Enable Depth Testing
   	 glEnable(GL_DEPTH_TEST); 
         return TRUE;

}

BOOL CGraphicsEditorView::SetupPixelFormat()
{
	 static PIXELFORMATDESCRIPTOR pfd = 
     {
        sizeof(PIXELFORMATDESCRIPTOR),  // size of this pfd
        1,                              // version number
        PFD_DRAW_TO_WINDOW |  PFD_SUPPORT_OPENGL  // support window | support //OpenGL| 
       | PFD_DOUBLEBUFFER , //double buffered
        PFD_TYPE_RGBA,                  // RGBA type
        24,                             // 24-bit color depth
        0, 0, 0, 0, 0, 0,               // color bits ignored
        0, 0, // no alpha buffer // shift bit ignored
        0,                              // no accumulation buffer
        0, 0, 0, 0,                     // accum bits ignored
        16, 0, // 16-bit z-buffer // no stencil buffer
        0, PFD_MAIN_PLANE, 0, // no auxiliary buffer // main layer// reserved
        0, 0, 0                         // layer masks ignored
        };
    
        int nPixelFormat = ChoosePixelFormat(m_pDC->GetSafeHdc(), &pfd);
        if (nPixelFormat == 0 )   return FALSE;
        if (SetPixelFormat(m_pDC->GetSafeHdc(), nPixelFormat, &pfd) == FALSE)   return FALSE;
        return TRUE;
}
//��ͼ����
void CGraphicsEditorView ::RenderScene( )
{ 
	for (int i=0; i<m_cgEntitys.size(); i++)
		m_cgEntitys[i]->Darw();
}

void CGraphicsEditorView::OnLButtonDown(UINT nFlags, CPoint point) 
{
	CPoint temp;
	temp.x = point.x;
	temp.y = m_iWindowHeight - point.y;

	if (m_cgCurrentEntity)//�༭״̬
	{
		m_cgCurrentEntity->OnLButtonDown(nFlags, temp); 
		
		if (m_cgCurrentEntity->m_eStatus == InputingEnd)//������������뵽����
		{	
			m_cgCurrentEntity->SetStatus(Selected);
			m_cgEntitys.push_back(m_cgCurrentEntity);
			
			//�����뷴����
			cgCommand c;
			
			c.pObj = m_cgCurrentEntity;
			c.commandType = NEW;
			m_cgComandManager.AddUndo(c);
			m_cgComandManager.ClearRedo();
			//

			m_cgCurrentEntity = 0;
		}
		Invalidate(FALSE);
	}

	else //����
	{
		float x = temp.x;
		float y = temp.y;

		for (int i=0; i<m_cgEntitys.size(); i++)
		{
		
			cgObject*pp = m_cgEntitys[i];//���Բ鿴��
			m_cgEntitys[i]->SetStatus(Drawing);
			if (m_cgEntitys[i]->HitTest(x,y))
			{
				m_cgEntitys[i]->SetStatus(Selected);	
				
				SetCursor(AfxGetApp()->LoadStandardCursor(IDC_SIZEALL ));
			}
		}
		
		Invalidate(FALSE);
	}
	
	
	CView::OnLButtonDown(nFlags, point);
}

void CGraphicsEditorView::OnMouseMove(UINT nFlags, CPoint point) 
{
	CPoint temp;
	temp.x = point.x;
	temp.y = m_iWindowHeight - point.y;

	if (m_cgCurrentEntity)
	{
		SetCursor(AfxGetApp()->LoadStandardCursor(IDC_CROSS));

		m_cgCurrentEntity->OnMouseMove(nFlags, temp) ;
		Invalidate(FALSE);
	}
	else
	{
		//�ƶ���굽ͼ����ʱ����ʾʮ�ֹ��
		BOOL hit = FALSE;
		for (int i=0; i<m_cgEntitys.size(); i++)
		{
			if (m_cgEntitys[i]->HitTest(temp.x,temp.y))
			{
				SetCursor(AfxGetApp()->LoadStandardCursor(IDC_SIZEALL ));
				hit = TRUE;
				break;
			}
		}
	
		if (!hit) SetCursor(AfxGetApp()->LoadStandardCursor(IDC_ARROW));
		
	}
	
	if (nFlags == MK_LBUTTON)
	{
		for (int i=0; i<m_cgEntitys.size(); i++)
		{
			m_cgEntitys[i]->OnMouseMove(nFlags, point);
		}
		Invalidate(FALSE);
	}
	
	CView::OnMouseMove(nFlags, point);
}
//==========����==============//
void CGraphicsEditorView::OnButtonLine() 
{
	cgLine *line = new cgLine();

	line->m_eStatus = Inputing;

	m_cgCurrentEntity = line;

	SetEntitysStatus(Drawing);//��ʰȡ��ͼ�λָ�������״̬
}

void CGraphicsEditorView::OnUpdateButtonLine(CCmdUI* pCmdUI) 
{
	if (!m_cgCurrentEntity)//��ǰ��ͼԪΪ��
	{
		pCmdUI->SetCheck(0);//��ѡ��
		return;
	}
	if (!m_cgCurrentEntity->m_eStatus == Inputing) pCmdUI->SetCheck(0);//�����inputing��ѡ��
	else pCmdUI->SetCheck(1);//�������ѡ��
	
}
//========��ͼԪ�ָ�������״̬
void CGraphicsEditorView::SetEntitysStatus(cgEntityStatus es)
{
	for (int i=0; i<m_cgEntitys.size(); i++) m_cgEntitys[i]->SetStatus(es);

}
//=======================����============================//
void CGraphicsEditorView::OnUpdateButtonPoint(CCmdUI* pCmdUI) 
{
	if (!m_cgCurrentEntity)//��ǰ��ͼԪΪ��
	{
		pCmdUI->SetCheck(0);//��ѡ��
		return;
	}
	if (!m_cgCurrentEntity->m_eStatus == Inputing) pCmdUI->SetCheck(0);//�����inputing��ѡ��
	else pCmdUI->SetCheck(1);//�������ѡ��
}

void CGraphicsEditorView::OnButtonPoint() 
{
	cgPoint *point = new cgPoint();

	point->m_eStatus = Inputing;//״̬Ϊ����

	m_cgCurrentEntity = point;

	SetEntitysStatus(Drawing);//��ʰȡ��ͼ�λָ�������״̬
	
}
//======================================================//


//==============��������=============================//
void CGraphicsEditorView::OnButtonTriangle() 
{
	// TODO: Add your command handler code here
	cgTriangle *triangle = new cgTriangle();//���������ζ��������������ͼ�ξͻ�һ����ͺ�

	triangle->m_eStatus = Inputing;//״̬Ϊ����

	m_cgCurrentEntity = triangle;

	SetEntitysStatus(Drawing);//��ʰȡ��ͼ�λָ�������״̬
}
/*���update��������Ҫ�ģ�ֱ�Ӵ�ֱ�ߵ��Ǹ����������ͺ�*/
void CGraphicsEditorView::OnUpdateButtonTriangle(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	if (!m_cgCurrentEntity)//��ǰ��ͼԪΪ��
	{
		pCmdUI->SetCheck(0);//��ѡ��
		return;
	}
	if (!m_cgCurrentEntity->m_eStatus == Inputing) pCmdUI->SetCheck(0);//�����inputing��ѡ��
	else pCmdUI->SetCheck(1);//�������ѡ��
}
///////////////////////////////////////////
//===========������===============//
void CGraphicsEditorView::OnButtonRectangle() 
{
	cgRectangle *rectangle = new cgRectangle();

	rectangle->m_eStatus = Inputing;

	m_cgCurrentEntity = rectangle;

	SetEntitysStatus(Drawing);//��ʰȡ��ͼ�λָ�������״̬
	
}

void CGraphicsEditorView::OnUpdateButtonRectangle(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
		if (!m_cgCurrentEntity)//��ǰ��ͼԪΪ��
	{
		pCmdUI->SetCheck(0);//��ѡ��
		return;
	}
	if (!m_cgCurrentEntity->m_eStatus == Inputing) pCmdUI->SetCheck(0);//�����inputing��ѡ��
	else pCmdUI->SetCheck(1);//�������ѡ��
}


//================�������===============//
void CGraphicsEditorView::OnButtonPolygon() 
{
	// TODO: Add your command handler code here
	cgPolygon *polygon = new cgPolygon();

	polygon->m_eStatus = Inputing;

	m_cgCurrentEntity = polygon;

	SetEntitysStatus(Drawing);//��ʰȡ��ͼ�λָ�������״̬
}

void CGraphicsEditorView::OnUpdateButtonPolygon(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
		if (!m_cgCurrentEntity)//��ǰ��ͼԪΪ��
	{
		pCmdUI->SetCheck(0);//��ѡ��
		return;
	}
	if (!m_cgCurrentEntity->m_eStatus == Inputing) pCmdUI->SetCheck(0);//�����inputing��ѡ��
	else pCmdUI->SetCheck(1);//�������ѡ��
}

//==================================//

void CGraphicsEditorView::OnRButtonDown(UINT nFlags, CPoint point) 
{
	CPoint temp;
	temp.x = point.x;
	temp.y = m_iWindowHeight - point.y;

	// TODO: Add your message handler code here and/or call default
	if (m_cgCurrentEntity)//�༭״̬
	{
		m_cgCurrentEntity->OnRButtonDown(nFlags,temp); 
		if (m_cgCurrentEntity->m_eStatus == InputingEnd)//������������뵽����
		{	
			m_cgCurrentEntity->SetStatus(Selected);
			m_cgEntitys.push_back(m_cgCurrentEntity);
			
			m_cgCurrentEntity = 0;
		}
		Invalidate(FALSE);
	}
	else //����
	{
		float x = temp.x;
		float y = temp.y;

		for (int i=0; i<m_cgEntitys.size(); i++)
		{
		
			cgObject*pp = m_cgEntitys[i];//���Բ鿴��
			m_cgEntitys[i]->SetStatus(Drawing);
			if (m_cgEntitys[i]->HitTest(x,y))
			{
				m_cgEntitys[i]->SetStatus(Selected);	
				
				SetCursor(AfxGetApp()->LoadStandardCursor(IDC_SIZEALL ));
			}
		}
		
		Invalidate(FALSE);
	}
	
	CView::OnRButtonDown(nFlags, point);
}

//=======������======//
void CGraphicsEditorView::OnButtonBackline() 
{
	// TODO: Add your command handler code here
	cgBackLine *backline = new cgBackLine();

	backline->m_eStatus = Inputing;

	m_cgCurrentEntity = backline;

	SetEntitysStatus(Drawing);//��ʰȡ��ͼ�λָ�������״̬
}

void CGraphicsEditorView::OnUpdateButtonBackline(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	if (!m_cgCurrentEntity)//��ǰ��ͼԪΪ��
	{
		pCmdUI->SetCheck(0);//��ѡ��
		return;
	}
	if (!m_cgCurrentEntity->m_eStatus == Inputing) pCmdUI->SetCheck(0);//�����inputing��ѡ��
	else pCmdUI->SetCheck(1);//�������ѡ��
}
//=======������======//

void CGraphicsEditorView::OnButtonCircle() 
{
	// TODO: Add your command handler code here
	cgCircle *circle = new cgCircle();

	circle->m_eStatus = Inputing;

	m_cgCurrentEntity = circle;

	SetEntitysStatus(Drawing);//��ʰȡ��ͼ�λָ�������״̬
}

void CGraphicsEditorView::OnUpdateButtonCircle(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	if (!m_cgCurrentEntity)//��ǰ��ͼԪΪ��
	{
		pCmdUI->SetCheck(0);//��ѡ��
		return;
	}
	if (!m_cgCurrentEntity->m_eStatus == Inputing) pCmdUI->SetCheck(0);//�����inputing��ѡ��
	else pCmdUI->SetCheck(1);//�������ѡ��
}

void CGraphicsEditorView::OnButtonB() 
{
	// TODO: Add your command handler code here
	cgBline *bline = new cgBline();

	bline->m_eStatus = Inputing;

	m_cgCurrentEntity = bline;

	SetEntitysStatus(Drawing);//��ʰȡ��ͼ�λָ�������״̬
}

void CGraphicsEditorView::OnUpdateButtonB(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	if (!m_cgCurrentEntity)//��ǰ��ͼԪΪ��
	{
		pCmdUI->SetCheck(0);//��ѡ��
		return;
	}
	if (!m_cgCurrentEntity->m_eStatus == Inputing) pCmdUI->SetCheck(0);//�����inputing��ѡ��
	else pCmdUI->SetCheck(1);//�������ѡ��
}

//�Ҽ������˵�����Ӧ����
void CGraphicsEditorView::OnContextMenu(CWnd* pWnd, CPoint point) 
{        
	CMenu menu; //����һ���˵�����        
	VERIFY(menu.LoadMenu(IDR_POP_MENU));//����ָ��ID�Ĳ˵�           
	CMenu* pPopup = menu.GetSubMenu(0);//����ȡ�ñ�ָ���˵����������ʽ�˵����Ӳ˵��ľ��         
	ASSERT(pPopup != NULL); //���Դ���
	
	CWnd* pWndPopupOwner = this;  //��õ�ǰ���ڵľ��         
	while (pWndPopupOwner->GetStyle() & WS_CHILD)            
		pWndPopupOwner = pWndPopupOwner->GetParent();           

	pPopup->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y,
		pWndPopupOwner);    
}

void CGraphicsEditorView::OnEditColor() 
{
		CColorDialog dlgColor;//������ɫ�Ի���
	cgObject *pObject=0;
	
	//��������ת�Ͷ�����б������ҳ���ǰѡ�е�ͼ�ζ���
	for (int i=0; i<m_cgEntitys.size(); i++)
	{
		if (m_cgEntitys[i]->GetStatus() == Selected || m_cgEntitys[i]->GetStatus() == Moving)
		//�ж��Ƿ�ѡ��
		{
			pObject = m_cgEntitys[i];
			break;
		}
	}

	if(!pObject) return;//���û��ͼ�α�ѡ�оͷ��أ���������Ҫ�ı�˵���״̬

	COLORREF color;

	color = RGB(pObject->GetColorR()*255,pObject->GetColorG()*255,pObject->GetColorB()*255);//��ȡ��ǰͼ�ε���ɫ
    dlgColor.m_cc.Flags |= CC_FULLOPEN|CC_RGBINIT;   // CC_RGBINIT�������ϴ�ѡ�����ɫ��Ϊ��ʼ��ɫ��ʾ����
    dlgColor.m_cc.rgbResult = color;        //��¼�ϴ�ѡ�����ɫ
	
	//������ɫ
	if(dlgColor.DoModal() == IDOK)
	{
		color = dlgColor.m_cc.rgbResult;
		
		int r = GetRValue(color);
		int g = GetGValue(color);
		int b = GetBValue(color);

		pObject->SetColor(r/255.0f,g/255.0f,b/255.0f);

		Invalidate(FALSE);//ǿ���ػ�
	}
}

void CGraphicsEditorView::OnUpdateEditColor(CCmdUI* pCmdUI) 
{
	//���û��ѡ��ͼԪ���������һ�ɫ
	pCmdUI->Enable(FALSE);
	for (int i=0; i<m_cgEntitys.size(); i++)
	{
		if (m_cgEntitys[i]->GetStatus() == Selected || m_cgEntitys[i]->GetStatus() == Moving)
		{
			pCmdUI->Enable(TRUE);
			return;
		}
	}
	
}

void CGraphicsEditorView::OnRedo() 
{
	m_cgComandManager.Redo(m_cgEntitys);
	Invalidate(FALSE);//ǿ���ػ�
}

void CGraphicsEditorView::OnUpdateRedo(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(!m_cgComandManager.IsRedoEmpty());
	
}

void CGraphicsEditorView::OnUndo() 
{
	m_cgComandManager.Undo(m_cgEntitys);
	Invalidate(FALSE);//ǿ���ػ�
}

void CGraphicsEditorView::OnUpdateUndo(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(!m_cgComandManager.IsUndoEmpty());
}

void CGraphicsEditorView::OnEditCut() 
{
		// ɾ��ѡ�е�ͼԪ
	for (int i=0; i<m_cgEntitys.size(); i++)
	{
		if (m_cgEntitys[i]->GetStatus() == Selected || m_cgEntitys[i]->GetStatus() == Moving)
		//�ж��Ƿ�ѡ��
		{
			cgObject *pObject = m_cgEntitys[i];
			m_cgEntitys.erase(m_cgEntitys.begin()+i);// ɾ��

			//�����뷴����
			cgCommand c;
			
			c.pObj = pObject;
			c.commandType = DELE;
			m_cgComandManager.AddUndo(c);
			m_cgComandManager.ClearRedo();
			//

			Invalidate(FALSE);//ǿ���ػ�
			return;
		}
	}
	
}

void CGraphicsEditorView::OnUpdateEditCut(CCmdUI* pCmdUI) 
{
//���û��ѡ��ͼԪ���������һ�ɫ
	pCmdUI->Enable(FALSE);
	for (int i=0; i<m_cgEntitys.size(); i++)
	{
		if (m_cgEntitys[i]->GetStatus() == Selected || m_cgEntitys[i]->GetStatus() == Moving)
		{
			pCmdUI->Enable(TRUE);
			return;
		}
	}
	
}
