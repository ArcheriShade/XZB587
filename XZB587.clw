; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CDlgHistogram
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "XZB587.h"
LastPage=0

ClassCount=6
Class1=CXZB587App
Class2=CXZB587Doc
Class3=CXZB587View
Class4=CMainFrame

ResourceCount=3
Resource1=IDD_ABOUTBOX
Class5=CAboutDlg
Resource2=IDD_DIALOG1
Class6=CDlgHistogram
Resource3=IDR_MAINFRAME

[CLS:CXZB587App]
Type=0
HeaderFile=XZB587.h
ImplementationFile=XZB587.cpp
Filter=N
LastObject=CXZB587App

[CLS:CXZB587Doc]
Type=0
HeaderFile=XZB587Doc.h
ImplementationFile=XZB587Doc.cpp
Filter=N
LastObject=CXZB587Doc
BaseClass=CDocument
VirtualFilter=DC

[CLS:CXZB587View]
Type=0
HeaderFile=XZB587View.h
ImplementationFile=XZB587View.cpp
Filter=C
LastObject=CXZB587View
BaseClass=CScrollView
VirtualFilter=VWC


[CLS:CMainFrame]
Type=0
HeaderFile=MainFrm.h
ImplementationFile=MainFrm.cpp
Filter=T
LastObject=ID_HISTOGRAM




[CLS:CAboutDlg]
Type=0
HeaderFile=XZB587.cpp
ImplementationFile=XZB587.cpp
Filter=D
LastObject=CAboutDlg

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=5
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889
Control5=IDC_STATIC,static,1342177287

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
Command1=ID_FILE_OPEN
Command2=ID_GRAY
Command3=ID_HISTOGRAM
CommandCount=3

[DLG:IDD_DIALOG1]
Type=1
Class=CDlgHistogram
ControlCount=2
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816

[CLS:CDlgHistogram]
Type=0
HeaderFile=DlgHistogram.h
ImplementationFile=DlgHistogram.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=CDlgHistogram

