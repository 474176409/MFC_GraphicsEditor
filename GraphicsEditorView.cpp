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
	RenderScene(); //具体的绘图函数，在 RC 中绘制

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
	
	wglMakeCurrent(m_pDC->m_hDC,NULL); //释放与m_hDC 对应的 RC
	wglDeleteContext(m_hRC); //删除 RC if (m_pDC)
	delete m_pDC; //删除当前 View 拥有的 DC 
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
//绘图函数
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

	if (m_cgCurrentEntity)//编辑状态
	{
		m_cgCurrentEntity->OnLButtonDown(nFlags, temp); 
		
		if (m_cgCurrentEntity->m_eStatus == InputingEnd)//如果定义好则加入到容器
		{	
			m_cgCurrentEntity->SetStatus(Selected);
			m_cgEntitys.push_back(m_cgCurrentEntity);
			
			//撤销与反撤销
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

	else //测试
	{
		float x = temp.x;
		float y = temp.y;

		for (int i=0; i<m_cgEntitys.size(); i++)
		{
		
			cgObject*pp = m_cgEntitys[i];//测试查看用
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
		//移动光标到图形上时，显示十字光标
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
//==========画线==============//
void CGraphicsEditorView::OnButtonLine() 
{
	cgLine *line = new cgLine();

	line->m_eStatus = Inputing;

	m_cgCurrentEntity = line;

	SetEntitysStatus(Drawing);//将拾取的图形恢复到绘制状态
}

void CGraphicsEditorView::OnUpdateButtonLine(CCmdUI* pCmdUI) 
{
	if (!m_cgCurrentEntity)//当前的图元为空
	{
		pCmdUI->SetCheck(0);//不选中
		return;
	}
	if (!m_cgCurrentEntity->m_eStatus == Inputing) pCmdUI->SetCheck(0);//如果是inputing则不选中
	else pCmdUI->SetCheck(1);//其余情况选中
	
}
//========将图元恢复到绘制状态
void CGraphicsEditorView::SetEntitysStatus(cgEntityStatus es)
{
	for (int i=0; i<m_cgEntitys.size(); i++) m_cgEntitys[i]->SetStatus(es);

}
//=======================画点============================//
void CGraphicsEditorView::OnUpdateButtonPoint(CCmdUI* pCmdUI) 
{
	if (!m_cgCurrentEntity)//当前的图元为空
	{
		pCmdUI->SetCheck(0);//不选中
		return;
	}
	if (!m_cgCurrentEntity->m_eStatus == Inputing) pCmdUI->SetCheck(0);//如果是inputing则不选中
	else pCmdUI->SetCheck(1);//其余情况选中
}

void CGraphicsEditorView::OnButtonPoint() 
{
	cgPoint *point = new cgPoint();

	point->m_eStatus = Inputing;//状态为输入

	m_cgCurrentEntity = point;

	SetEntitysStatus(Drawing);//将拾取的图形恢复到绘制状态
	
}
//======================================================//


//==============画三角形=============================//
void CGraphicsEditorView::OnButtonTriangle() 
{
	// TODO: Add your command handler code here
	cgTriangle *triangle = new cgTriangle();//创建三角形对象，如果是其他的图形就换一下类就好

	triangle->m_eStatus = Inputing;//状态为输入

	m_cgCurrentEntity = triangle;

	SetEntitysStatus(Drawing);//将拾取的图形恢复到绘制状态
}
/*这个update函数不需要改，直接从直线的那个函数里拷贝就好*/
void CGraphicsEditorView::OnUpdateButtonTriangle(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	if (!m_cgCurrentEntity)//当前的图元为空
	{
		pCmdUI->SetCheck(0);//不选中
		return;
	}
	if (!m_cgCurrentEntity->m_eStatus == Inputing) pCmdUI->SetCheck(0);//如果是inputing则不选中
	else pCmdUI->SetCheck(1);//其余情况选中
}
///////////////////////////////////////////
//===========画矩形===============//
void CGraphicsEditorView::OnButtonRectangle() 
{
	cgRectangle *rectangle = new cgRectangle();

	rectangle->m_eStatus = Inputing;

	m_cgCurrentEntity = rectangle;

	SetEntitysStatus(Drawing);//将拾取的图形恢复到绘制状态
	
}

void CGraphicsEditorView::OnUpdateButtonRectangle(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
		if (!m_cgCurrentEntity)//当前的图元为空
	{
		pCmdUI->SetCheck(0);//不选中
		return;
	}
	if (!m_cgCurrentEntity->m_eStatus == Inputing) pCmdUI->SetCheck(0);//如果是inputing则不选中
	else pCmdUI->SetCheck(1);//其余情况选中
}


//================画多边形===============//
void CGraphicsEditorView::OnButtonPolygon() 
{
	// TODO: Add your command handler code here
	cgPolygon *polygon = new cgPolygon();

	polygon->m_eStatus = Inputing;

	m_cgCurrentEntity = polygon;

	SetEntitysStatus(Drawing);//将拾取的图形恢复到绘制状态
}

void CGraphicsEditorView::OnUpdateButtonPolygon(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
		if (!m_cgCurrentEntity)//当前的图元为空
	{
		pCmdUI->SetCheck(0);//不选中
		return;
	}
	if (!m_cgCurrentEntity->m_eStatus == Inputing) pCmdUI->SetCheck(0);//如果是inputing则不选中
	else pCmdUI->SetCheck(1);//其余情况选中
}

//==================================//

void CGraphicsEditorView::OnRButtonDown(UINT nFlags, CPoint point) 
{
	CPoint temp;
	temp.x = point.x;
	temp.y = m_iWindowHeight - point.y;

	// TODO: Add your message handler code here and/or call default
	if (m_cgCurrentEntity)//编辑状态
	{
		m_cgCurrentEntity->OnRButtonDown(nFlags,temp); 
		if (m_cgCurrentEntity->m_eStatus == InputingEnd)//如果定义好则加入到容器
		{	
			m_cgCurrentEntity->SetStatus(Selected);
			m_cgEntitys.push_back(m_cgCurrentEntity);
			
			m_cgCurrentEntity = 0;
		}
		Invalidate(FALSE);
	}
	else //测试
	{
		float x = temp.x;
		float y = temp.y;

		for (int i=0; i<m_cgEntitys.size(); i++)
		{
		
			cgObject*pp = m_cgEntitys[i];//测试查看用
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

//=======画折线======//
void CGraphicsEditorView::OnButtonBackline() 
{
	// TODO: Add your command handler code here
	cgBackLine *backline = new cgBackLine();

	backline->m_eStatus = Inputing;

	m_cgCurrentEntity = backline;

	SetEntitysStatus(Drawing);//将拾取的图形恢复到绘制状态
}

void CGraphicsEditorView::OnUpdateButtonBackline(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	if (!m_cgCurrentEntity)//当前的图元为空
	{
		pCmdUI->SetCheck(0);//不选中
		return;
	}
	if (!m_cgCurrentEntity->m_eStatus == Inputing) pCmdUI->SetCheck(0);//如果是inputing则不选中
	else pCmdUI->SetCheck(1);//其余情况选中
}
//=======画折线======//

void CGraphicsEditorView::OnButtonCircle() 
{
	// TODO: Add your command handler code here
	cgCircle *circle = new cgCircle();

	circle->m_eStatus = Inputing;

	m_cgCurrentEntity = circle;

	SetEntitysStatus(Drawing);//将拾取的图形恢复到绘制状态
}

void CGraphicsEditorView::OnUpdateButtonCircle(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	if (!m_cgCurrentEntity)//当前的图元为空
	{
		pCmdUI->SetCheck(0);//不选中
		return;
	}
	if (!m_cgCurrentEntity->m_eStatus == Inputing) pCmdUI->SetCheck(0);//如果是inputing则不选中
	else pCmdUI->SetCheck(1);//其余情况选中
}

void CGraphicsEditorView::OnButtonB() 
{
	// TODO: Add your command handler code here
	cgBline *bline = new cgBline();

	bline->m_eStatus = Inputing;

	m_cgCurrentEntity = bline;

	SetEntitysStatus(Drawing);//将拾取的图形恢复到绘制状态
}

void CGraphicsEditorView::OnUpdateButtonB(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	if (!m_cgCurrentEntity)//当前的图元为空
	{
		pCmdUI->SetCheck(0);//不选中
		return;
	}
	if (!m_cgCurrentEntity->m_eStatus == Inputing) pCmdUI->SetCheck(0);//如果是inputing则不选中
	else pCmdUI->SetCheck(1);//其余情况选中
}

//右键弹出菜单的响应函数
void CGraphicsEditorView::OnContextMenu(CWnd* pWnd, CPoint point) 
{        
	CMenu menu; //创建一个菜单对象        
	VERIFY(menu.LoadMenu(IDR_POP_MENU));//载入指定ID的菜单           
	CMenu* pPopup = menu.GetSubMenu(0);//函数取得被指定菜单激活的下拉式菜单或子菜单的句柄         
	ASSERT(pPopup != NULL); //断言处理
	
	CWnd* pWndPopupOwner = this;  //获得当前窗口的句柄         
	while (pWndPopupOwner->GetStyle() & WS_CHILD)            
		pWndPopupOwner = pWndPopupOwner->GetParent();           

	pPopup->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y,
		pWndPopupOwner);    
}

void CGraphicsEditorView::OnEditColor() 
{
		CColorDialog dlgColor;//创建颜色对话框
	cgObject *pObject=0;
	
	//对整个上转型对象进行遍历，找出当前选中的图形对象
	for (int i=0; i<m_cgEntitys.size(); i++)
	{
		if (m_cgEntitys[i]->GetStatus() == Selected || m_cgEntitys[i]->GetStatus() == Moving)
		//判断是否选中
		{
			pObject = m_cgEntitys[i];
			break;
		}
	}

	if(!pObject) return;//如果没有图形被选中就返回，这样不需要改变菜单的状态

	COLORREF color;

	color = RGB(pObject->GetColorR()*255,pObject->GetColorG()*255,pObject->GetColorB()*255);//获取当前图形的颜色
    dlgColor.m_cc.Flags |= CC_FULLOPEN|CC_RGBINIT;   // CC_RGBINIT可以让上次选择的颜色作为初始颜色显示出来
    dlgColor.m_cc.rgbResult = color;        //记录上次选择的颜色
	
	//更新颜色
	if(dlgColor.DoModal() == IDOK)
	{
		color = dlgColor.m_cc.rgbResult;
		
		int r = GetRValue(color);
		int g = GetGValue(color);
		int b = GetBValue(color);

		pObject->SetColor(r/255.0f,g/255.0f,b/255.0f);

		Invalidate(FALSE);//强制重绘
	}
}

void CGraphicsEditorView::OnUpdateEditColor(CCmdUI* pCmdUI) 
{
	//如果没有选择图元，不可用且灰色
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
	Invalidate(FALSE);//强制重绘
}

void CGraphicsEditorView::OnUpdateRedo(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(!m_cgComandManager.IsRedoEmpty());
	
}

void CGraphicsEditorView::OnUndo() 
{
	m_cgComandManager.Undo(m_cgEntitys);
	Invalidate(FALSE);//强制重绘
}

void CGraphicsEditorView::OnUpdateUndo(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(!m_cgComandManager.IsUndoEmpty());
}

void CGraphicsEditorView::OnEditCut() 
{
		// 删除选中的图元
	for (int i=0; i<m_cgEntitys.size(); i++)
	{
		if (m_cgEntitys[i]->GetStatus() == Selected || m_cgEntitys[i]->GetStatus() == Moving)
		//判断是否选中
		{
			cgObject *pObject = m_cgEntitys[i];
			m_cgEntitys.erase(m_cgEntitys.begin()+i);// 删除

			//撤销与反撤销
			cgCommand c;
			
			c.pObj = pObject;
			c.commandType = DELE;
			m_cgComandManager.AddUndo(c);
			m_cgComandManager.ClearRedo();
			//

			Invalidate(FALSE);//强制重绘
			return;
		}
	}
	
}

void CGraphicsEditorView::OnUpdateEditCut(CCmdUI* pCmdUI) 
{
//如果没有选择图元，不可用且灰色
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
