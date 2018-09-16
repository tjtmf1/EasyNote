#pragma once
#include "afxwin.h"
#include "afxcmn.h"
#include "ShowTable.h"

// CAlterTable ��ȭ �����Դϴ�.

class CShowTable;

class CAlterTable : public CDialog
{
	DECLARE_DYNAMIC(CAlterTable)

public:
	CAlterTable(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CAlterTable();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_ALT_TABLE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	CEdit m_day;

	CEdit m_time1;
	CEdit m_time2;
	CEdit m_time3;
	CEdit m_time4;

	CSpinButtonCtrl m_spin1;
	CSpinButtonCtrl m_spin2;
	CSpinButtonCtrl m_spin3;
	CSpinButtonCtrl m_spin4;

	CEdit m_className;

	CShowTable* m_MainWnd;

public:
	void saveData();
	void DeleteData();
	void ChangeLine();
};
