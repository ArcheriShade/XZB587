// XZB587Doc.cpp : implementation of the CXZB587Doc class
//

#include "stdafx.h"
#include "XZB587.h"

#include "XZB587Doc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CXZB587Doc

IMPLEMENT_DYNCREATE(CXZB587Doc, CDocument)

BEGIN_MESSAGE_MAP(CXZB587Doc, CDocument)
	//{{AFX_MSG_MAP(CXZB587Doc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CXZB587Doc construction/destruction

CXZB587Doc::CXZB587Doc()
{
	// TODO: add one-time construction code here

}

CXZB587Doc::~CXZB587Doc()
{
}

BOOL CXZB587Doc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CXZB587Doc serialization

void CXZB587Doc::Serialize(CArchive& ar)
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
// CXZB587Doc diagnostics

#ifdef _DEBUG
void CXZB587Doc::AssertValid() const
{
	CDocument::AssertValid();
}

void CXZB587Doc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CXZB587Doc commands

BOOL LoadBmpFile(char* BmpFileName);
BOOL CXZB587Doc::OnOpenDocument(LPCTSTR lpszPathName) 
{
	if (!CDocument::OnOpenDocument(lpszPathName))
		return FALSE;
	
	// TODO: Add your specialized creation code here
	LoadBmpFile((char*) lpszPathName);
	return TRUE;
}