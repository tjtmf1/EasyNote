#pragma once
#include "afxwin.h"
#include "ShowTable.h"

// CAddTable ��ȭ �����Դϴ�.

class CShowTable;

class CAddTable : public CDialog
{
	DECLARE_DYNAMIC(CAddTable)

public:
	CAddTable(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CAddTable();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_ADD_TABLE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
	virtual void OnOK();
public:
	CEdit m_time1;
	CEdit m_time2;
	CEdit m_time3;
	CEdit m_time4;

	CSpinButtonCtrl m_spin1;
	CSpinButtonCtrl m_spin2;
	CSpinButtonCtrl m_spin3;
	CSpinButtonCtrl m_spin4;

	CEdit m_className;
	CEdit m_day;

	virtual BOOL OnInitDialog();
	void AddToList();
	CShowTable* m_MainWnd;
};
