#pragma once
#include "Pipe.h"
#include "afxwin.h"
#include "MainFrm.h"
#include "SetTitle.h"

// CRecordButton �� ���Դϴ�.

class CRecordButton : public CFormView, CPipe
{
	DECLARE_DYNCREATE(CRecordButton)

protected:
	CRecordButton();           // ���� ����⿡ ���Ǵ� protected �������Դϴ�.
	virtual ~CRecordButton();

public:
	enum { IDD = IDD_RECORD_PLAY };
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
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	void OnEndOfPlayingFile();	// overload virtual function
	CButton m_RecButton;
	CButton m_PlayButton;
	bool m_bRec;
	bool m_bPlay;
	bool m_bBookMark;
	afx_msg void OnBnClickedButton5();
	void AddToBookMark();
	int m_playNum;
	virtual void OnUpdate(CView* /*pSender*/, LPARAM /*lHint*/, CObject* /*pHint*/);
};


