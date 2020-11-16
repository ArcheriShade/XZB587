// XZB587View.cpp : implementation of the CXZB587View class
//

#include "stdafx.h"
#include "XZB587.h"

#include "XZB587Doc.h"
#include "XZB587View.h"

#include "DlgHistogram.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CXZB587View

IMPLEMENT_DYNCREATE(CXZB587View, CScrollView)

BEGIN_MESSAGE_MAP(CXZB587View, CScrollView)
	//{{AFX_MSG_MAP(CXZB587View)
	ON_COMMAND(ID_GRAY, OnGray)
	ON_UPDATE_COMMAND_UI(ID_GRAY, OnUpdateGray)
	ON_WM_MOUSEMOVE()
	ON_COMMAND(ID_HISTOGRAM, OnHistogram)
	ON_UPDATE_COMMAND_UI(ID_HISTOGRAM, OnUpdateHistogram)
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CScrollView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CXZB587View construction/destruction

CXZB587View::CXZB587View()
{
	// TODO: add construction code here

}

CXZB587View::~CXZB587View()
{
}

BOOL CXZB587View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CScrollView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CXZB587View drawing

extern BITMAPINFO* lpBitsInfo;
void CXZB587View::OnDraw(CDC* pDC)
{
	CXZB587Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here

	if (NULL == lpBitsInfo)
		return;

	LPVOID lpBits = (LPVOID)&lpBitsInfo->bmiColors[lpBitsInfo->bmiHeader.biClrUsed];
	
	StretchDIBits( 
		pDC->GetSafeHdc(),
		0, 0, 
		lpBitsInfo->bmiHeader.biWidth, lpBitsInfo->bmiHeader.biHeight,
		0, 0, 
		lpBitsInfo->bmiHeader.biWidth, lpBitsInfo->bmiHeader.biHeight,
		lpBits, lpBitsInfo,
		DIB_RGB_COLORS, SRCCOPY
	);
}

void CXZB587View::OnInitialUpdate()
{
	CScrollView::OnInitialUpdate();

	CSize sizeTotal;
	// TODO: calculate the total size of this view
	sizeTotal.cx = sizeTotal.cy = 1200;
	SetScrollSizes(MM_TEXT, sizeTotal);
}

/////////////////////////////////////////////////////////////////////////////
// CXZB587View printing

BOOL CXZB587View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CXZB587View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CXZB587View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CXZB587View diagnostics

#ifdef _DEBUG
void CXZB587View::AssertValid() const
{
	CScrollView::AssertValid();
}

void CXZB587View::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}

CXZB587Doc* CXZB587View::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CXZB587Doc)));
	return (CXZB587Doc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CXZB587View message handlers

BOOL gray();
void CXZB587View::OnGray() 
{
	// TODO: Add your command handler code here
	gray();
	Invalidate();
}

BOOL isGray();
void CXZB587View::OnUpdateGray(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(lpBitsInfo != NULL && !isGray());
}

void pixel(int i, int j, char* str);
void CXZB587View::OnMouseMove(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	char xy[100];
	memset(xy, 0, 100);	//清空
	sprintf(xy, "x:%d y:%d    ", point.x, point.y);

	char rgb[100];
	memset(rgb, 0, 100);	//清空
	pixel(point.y, point.x, rgb);		//i控制行，j控制列

	strcat(xy, rgb);
	
	((CFrameWnd*)GetParent())->SetMessageText(xy);

	CScrollView::OnMouseMove(nFlags, point);
}

void CXZB587View::OnHistogram() 
{
	// TODO: Add your command handler code here
	// 推荐在图片旁边显示直方图
	CDlgHistogram dlg;
	dlg.DoModal();
}

void CXZB587View::OnUpdateHistogram(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(lpBitsInfo != NULL && (1 != lpBitsInfo->bmiHeader.biBitCount));
}
