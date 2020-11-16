// XZB587View.h : interface of the CXZB587View class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_XZB587VIEW_H__927A26AA_53D3_43B0_BE60_651B8E132558__INCLUDED_)
#define AFX_XZB587VIEW_H__927A26AA_53D3_43B0_BE60_651B8E132558__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CXZB587View : public CScrollView
{
protected: // create from serialization only
	CXZB587View();
	DECLARE_DYNCREATE(CXZB587View)

// Attributes
public:
	CXZB587Doc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CXZB587View)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual void OnInitialUpdate(); // called first time after construct
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CXZB587View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CXZB587View)
	afx_msg void OnGray();
	afx_msg void OnUpdateGray(CCmdUI* pCmdUI);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnHistogram();
	afx_msg void OnUpdateHistogram(CCmdUI* pCmdUI);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in XZB587View.cpp
inline CXZB587Doc* CXZB587View::GetDocument()
   { return (CXZB587Doc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_XZB587VIEW_H__927A26AA_53D3_43B0_BE60_651B8E132558__INCLUDED_)
