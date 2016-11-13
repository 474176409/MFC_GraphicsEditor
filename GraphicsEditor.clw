; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CGraphicsEditorView
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "GraphicsEditor.h"
LastPage=0

ClassCount=5
Class1=CGraphicsEditorApp
Class2=CGraphicsEditorDoc
Class3=CGraphicsEditorView
Class4=CMainFrame

ResourceCount=3
Resource1=IDR_MAINFRAME
Class5=CAboutDlg
Resource2=IDR_POP_MENU
Resource3=IDD_ABOUTBOX

[CLS:CGraphicsEditorApp]
Type=0
HeaderFile=GraphicsEditor.h
ImplementationFile=GraphicsEditor.cpp
Filter=N

[CLS:CGraphicsEditorDoc]
Type=0
HeaderFile=GraphicsEditorDoc.h
ImplementationFile=GraphicsEditorDoc.cpp
Filter=N

[CLS:CGraphicsEditorView]
Type=0
HeaderFile=GraphicsEditorView.h
ImplementationFile=GraphicsEditorView.cpp
Filter=C
BaseClass=CView
VirtualFilter=VWC
LastObject=ID_EDIT_CUT


[CLS:CMainFrame]
Type=0
HeaderFile=MainFrm.h
ImplementationFile=MainFrm.cpp
Filter=T
LastObject=ID_EDIT_CUT
BaseClass=CFrameWnd
VirtualFilter=fWC




[CLS:CAboutDlg]
Type=0
HeaderFile=GraphicsEditor.cpp
ImplementationFile=GraphicsEditor.cpp
Filter=D
LastObject=CAboutDlg

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[MNU:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_FILE_SAVE_AS
Command5=ID_FILE_PRINT
Command6=ID_FILE_PRINT_PREVIEW
Command7=ID_FILE_PRINT_SETUP
Command8=ID_FILE_MRU_FILE1
Command9=ID_APP_EXIT
Command10=ID_EDIT_UNDO
Command11=ID_EDIT_CUT
Command12=ID_EDIT_COPY
Command13=ID_EDIT_PASTE
Command14=ID_VIEW_TOOLBAR
Command15=ID_VIEW_STATUS_BAR
Command16=ID_APP_ABOUT
CommandCount=16

[ACL:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_FILE_PRINT
Command5=ID_EDIT_UNDO
Command6=ID_EDIT_CUT
Command7=ID_EDIT_COPY
Command8=ID_EDIT_PASTE
Command9=ID_EDIT_UNDO
Command10=ID_EDIT_CUT
Command11=ID_EDIT_COPY
Command12=ID_EDIT_PASTE
Command13=ID_NEXT_PANE
Command14=ID_PREV_PANE
CommandCount=14

[TB:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_EDIT_CUT
Command5=ID_EDIT_COPY
Command6=ID_EDIT_PASTE
Command7=ID_FILE_PRINT
Command8=ID_APP_ABOUT
Command9=ID_BUTTON_LINE
Command10=ID_BUTTON_POINT
Command11=ID_BUTTON_TRIANGLE
Command12=ID_BUTTON_RECTANGLE
Command13=ID_BUTTON_POLYGON
Command14=ID_BUTTON_BACKLINE
Command15=ID_BUTTON_CIRCLE
Command16=ID_BUTTON_B
Command17=ID_UNDO
Command18=ID_REDO
CommandCount=18

[MNU:IDR_POP_MENU]
Type=1
Class=CGraphicsEditorView
Command1=ID_EDIT_CUT
Command2=ID_EDIT_COLOR
CommandCount=2

