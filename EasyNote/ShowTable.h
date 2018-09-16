#pragma once
#include "afxcmn.h"
#include "AddTable.h"
#include "AlterTable.h"

// CShowTable ��ȭ �����Դϴ�.

class CShowTable : public CDialog
{
	DECLARE_DYNAMIC(CShowTable)

public:
	CShowTable(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CShowTable();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_SHOW_TABLE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

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
