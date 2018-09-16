#pragma once
#include "afxcmn.h"
#include "AddTable.h"
#include "AlterTable.h"

// CShowTable 대화 상자입니다.

class CShowTable : public CDialog
{
	DECLARE_DYNAMIC(CShowTable)

public:
	CShowTable(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CShowTable();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_SHOW_TABLE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	CListCtrl m_list;
	virtual BOOL OnInitDialog();

	void fill_list();
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnLvnItemchangedList1(NMHDR *pNMHDR, LRESULT *pResult);
	int m_selected;
	void DeleteData();
	int m_listCount;
};
