// XZB587Doc.h : interface of the CXZB587Doc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_XZB587DOC_H__DC30FAE3_93B9_4B0E_A0E9_82069A6D9401__INCLUDED_)
#define AFX_XZB587DOC_H__DC30FAE3_93B9_4B0E_A0E9_82069A6D9401__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CXZB587Doc : public CDocument
{
protected: // create from serialization only
	CXZB587Doc();
	DECLARE_DYNCREATE(CXZB587Doc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CXZB587Doc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CXZB587Doc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CXZB587Doc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_XZB587DOC_H__DC30FAE3_93B9_4B0E_A0E9_82069A6D9401__INCLUDED_)
