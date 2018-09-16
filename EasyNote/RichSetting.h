#pragma once
#include "MainFrm.h"
#include "NoteArea.h"
#include "afxext.h"

// CRichSetting 폼 뷰입니다.

class CRichSetting : public CFormView
{
	DECLARE_DYNCREATE(CRichSetting)

protected:
	CRichSetting();           // 동적 만들기에 사용되는 protected 생성자입니다.
	virtual ~CRichSetting();

public:
	enum { IDD = IDD_RICH_SETTING };
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()

	virtual void OnInitialUpdate();
public:
	CMFCColorButton m_fontColor;
	CSpinButtonCtrl m_spin;
	CMFCColorButton m_fontBg;
	bool m_markPen;
	bool m_bold;
	long m_tab;
	int m_diagram;
	bool m_fontRed;
	CEdit m_fontSize;
	int m_count;

	CRichEditCtrl* m_rich;

	virtual BOOL PreTranslateMessage(MSG* pMsg);

	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnCbnSelchangeCombo1();
	afx_msg void OnEnChangeEdit1();
	afx_msg void OnBnClickedMfccolorbutton2();
	afx_msg void OnBnClickedMfccolorbutton1();
	afx_msg void OnBnClickedButton7();
	afx_msg void OnBnClickedButton6();
	afx_msg void OnBnClickedButton5();
	afx_msg void OnBnClickedButton4();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton1();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	CBitmapButton m_pen;
};


