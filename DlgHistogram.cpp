// DlgHistogram.cpp : implementation file
//

#include "stdafx.h"
#include "XZB587.h"
#include "DlgHistogram.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgHistogram dialog


CDlgHistogram::CDlgHistogram(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgHistogram::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgHistogram)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CDlgHistogram::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgHistogram)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgHistogram, CDialog)
	//{{AFX_MSG_MAP(CDlgHistogram)
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgHistogram message handlers

extern DWORD H[256];
void Histogram();
BOOL CDlgHistogram::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	Histogram();	//在初始化对话框时生成直方数组
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgHistogram::OnPaint() 
{	//利用直方数组绘制直方图
	CPaintDC dc(this); // device context for painting
	
	// TODO: Add your message handler code here
	dc.Rectangle(20, 20, 20+256+1, 20+200+1);

	DWORD max = 0;
	int i;
	for (i = 0; i < 256; i++) {
		if (H[i] > max)
			max = H[i];
	}
	for (i = 0; i < 256; i++) {
		dc.MoveTo(20+i, 20+200);
		dc.LineTo(20+i, (20+200) - (int)(H[i]*200/max));
	}
	
	// Do not call CDialog::OnPaint() for painting messages
}
