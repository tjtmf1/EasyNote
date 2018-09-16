#pragma once
#include "afxcmn.h"
#include "BookMark.h"
#include "Pipe.h"

// CBookmarkList �� ���Դϴ�.

class CBookmarkList : public CFormView, CPipe
{
	DECLARE_DYNCREATE(CBookmarkList)

public:
	CBookmarkList();           // ���� ����⿡ ���Ǵ� protected �������Դϴ�.
	virtual ~CBookmarkList();

public:
	enum { IDD = IDD_RECORD_BOOKMARK };
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
	CListCtrl m_list;
	virtual void OnInitialUpdate();
	afx_msg void OnNMDblclkBookList(NMHDR *pNMHDR, LRESULT *pResult);
	int m_item;
};


