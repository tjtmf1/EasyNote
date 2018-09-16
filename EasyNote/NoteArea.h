#pragma once
#include "afxrich.h"
#include "EasyNote.h"
#include "afxcmn.h"
#include "MainFrm.h"
#include "RichSetting.h"
// CNoteArea 폼 뷰입니다.

class CRichSetting;

class CNoteArea : public CRichEditView
{
	DECLARE_DYNCREATE(CNoteArea)

protected:
	CNoteArea();           // 동적 만들기에 사용되는 protected 생성자입니다.
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
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.
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


