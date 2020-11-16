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

extern DWORD HGray[256];
extern DWORD HRad[256];
extern DWORD HGreen[256];
extern DWORD HBlue[256];
BOOL isGray();
void Histogram();

int hstgrmHeight = 100;
BOOL CDlgHistogram::OnInitDialog() 
{
	CDialog::OnInitDialog();

	int dlgHeight, width;

	width = 520;
	if (isGray())
		dlgHeight = 20 + hstgrmHeight + 50;
	else 
		dlgHeight = 20 + hstgrmHeight*3 + 20*2 + 50;

	CRect temprect(0,0,width,dlgHeight);	//指定对话框宽高
	CWnd::SetWindowPos(NULL,0,0,temprect.Width(),temprect.Height(),SWP_NOZORDER|SWP_NOMOVE);
	
	// TODO: Add extra initialization here
	Histogram();	//在初始化对话框时生成直方数组
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgHistogram::OnPaint() 
{	//利用直方数组绘制直方图
	CPaintDC dc(this); // device context for painting

	// TODO: Add your message handler code here
	int i, k;
	DWORD maxGray, maxR, maxG, maxB;
	maxGray = maxR = maxG = maxB = 0;
	if (isGray()) {
		dc.Rectangle(20, 20, 20+256+1, 20+hstgrmHeight+1);

		for (i = 0; i < 256; i++) {
			if (HGray[i] > maxGray)
				maxGray = HGray[i];
		}
		for (i = 0; i < 256; i++) {
			dc.MoveTo(20+i, 20+hstgrmHeight);
			dc.LineTo(20+i, (20+hstgrmHeight) - (int)(HGray[i]*hstgrmHeight/maxGray));
		}
	}
	else {
		for (k = 0; k < 3; k++)
			dc.Rectangle(20, 20+(20+hstgrmHeight+1)*k, 20+256+1, 20+hstgrmHeight+1+(20+hstgrmHeight+1)*k);
		
		for (i = 0; i < 256; i++) {
			if (HRad[i] > maxR)
				maxR = HRad[i];
			if (HGreen[i] > maxG)
				maxG = HGreen[i];
			if (HBlue[i] > maxB)
				maxB = HBlue[i];
		}
		for (i = 0; i < 256; i++) {
			dc.MoveTo(20+i, 20+hstgrmHeight+(20+hstgrmHeight+1)*0);
			dc.LineTo(20+i, (20+hstgrmHeight) - (int)(HRad[i]*hstgrmHeight/maxR));
		}
		for (i = 0; i < 256; i++) {
			dc.MoveTo(20+i, 20+hstgrmHeight+(20+hstgrmHeight+1)*1);
			dc.LineTo(20+i, (20+hstgrmHeight+(20+hstgrmHeight+1)*1) - (int)(HGreen[i]*hstgrmHeight/maxG));
		}
		for (i = 0; i < 256; i++) {
			dc.MoveTo(20+i, 20+hstgrmHeight+(20+hstgrmHeight+1)*2);
			dc.LineTo(20+i, (20+hstgrmHeight+(20+hstgrmHeight+1)*2) - (int)(HBlue[i]*hstgrmHeight/maxB));
		}
	}
	
	// Do not call CDialog::OnPaint() for painting messages
}
