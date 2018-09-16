#pragma once
#include "afxwin.h"
#include "afxcmn.h"
#include "ShowTable.h"

// CAlterTable 대화 상자입니다.

class CShowTable;

class CAlterTable : public CDialog
{
	DECLARE_DYNAMIC(CAlterTable)

public:
	CAlterTable(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CAlterTable();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_ALT_TABLE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

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
