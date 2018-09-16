#pragma once
#include "afxcmn.h"
#include "afxrich.h"
#include "afxwin.h"
#include "MainFrm.h"

// CNoteList �� ���Դϴ�.

class CNoteList : public CFormView
{
	DECLARE_DYNCREATE(CNoteList)

protected:
	CNoteList();           // ���� ����⿡ ���Ǵ� protected �������Դϴ�.
	virtual ~CNoteList();

public:
	enum { IDD = IDD_NOTE_LIST };
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	void AddToList(CString name, CString path);

	int m_listCount;
	virtual void OnInitialUpdate();
	CListCtrl m_list;
	afx_msg void OnLvnItemchangedList1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMDblclkList1(NMHDR *pNMHDR, LRESULT *pResult);
};


