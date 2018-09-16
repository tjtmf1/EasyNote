#pragma once
#include "afxwin.h"
#include "ShowTable.h"

// CAddTable 대화 상자입니다.

class CShowTable;

class CAddTable : public CDialog
{
	DECLARE_DYNAMIC(CAddTable)

public:
	CAddTable(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CAddTable();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_ADD_TABLE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

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
