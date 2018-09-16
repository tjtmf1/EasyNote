#pragma once
#include "afxrich.h"
#include "EasyNote.h"
#include "afxcmn.h"
#include "MainFrm.h"
#include "RichSetting.h"
// CNoteArea �� ���Դϴ�.

class CRichSetting;

class CNoteArea : public CRichEditView
{
	DECLARE_DYNCREATE(CNoteArea)

protected:
	CNoteArea();           // ���� ����⿡ ���Ǵ� protected �������Դϴ�.
	virtual ~CNoteArea();

public:
	enum { IDD = IDD_NOTE_AREA };
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.
	afx_msg void OnDestroy();
	DECLARE_MESSAGE_MAP()

public:
	void ReadData(DWORD_PTR data);

	CRichSetting* m_setting;

	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	virtual void OnInitialUpdate();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
};


