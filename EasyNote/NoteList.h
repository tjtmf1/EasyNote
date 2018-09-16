#pragma once
#include "afxcmn.h"
#include "afxrich.h"
#include "afxwin.h"
#include "MainFrm.h"

// CNoteList 폼 뷰입니다.

class CNoteList : public CFormView
{
	DECLARE_DYNCREATE(CNoteList)

protected:
	CNoteList();           // 동적 만들기에 사용되는 protected 생성자입니다.
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
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	void AddToList(CString name, CString path);

	int m_listCount;
	virtual void OnInitialUpdate();
	CListCtrl m_list;
	afx_msg void OnLvnItemchangedList1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMDblclkList1(NMHDR *pNMHDR, LRESULT *pResult);
};


