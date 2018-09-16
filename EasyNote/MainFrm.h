
// MainFrm.h : CMainFrame Ŭ������ �������̽�
//

#pragma once

#include "afxrich.h"
#include "NoteList.h"
#include "NoteArea.h"
#include "AddTable.h"
#include "ShowTable.h"
#include "RecordButton.h"
#include "BookmarkList.h"
#include "EasyNote.h"
#include "EasySplitterWnd.h"
#include "EasyNoteDoc.h"
#include "RichSetting.h"

class CMainFrame : public CFrameWnd
{
	
protected: // serialization������ ��������ϴ�.
	CMainFrame();
	DECLARE_DYNCREATE(CMainFrame)

// Ư���Դϴ�.
public:

// �۾��Դϴ�.
public:

// �������Դϴ�.
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// �����Դϴ�.
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // ��Ʈ�� ������ ���Ե� ����Դϴ�.
	CToolBar          m_wndToolBar;
	CStatusBar        m_wndStatusBar;

// ������ �޽��� �� �Լ�
protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	DECLARE_MESSAGE_MAP()

public:
	CEasySplitterWnd m_MainSplitter;
	CEasySplitterWnd m_CenterSplitter;
	CEasySplitterWnd m_RightSplitter;
	CEasySplitterWnd m_LeftSplitter;

	virtual BOOL OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext);
	afx_msg void OnShowTable();
	afx_msg void OnBookLoad();
	afx_msg void OnLoadNote();
	afx_msg void OnLoadNoteByPath(CString path);

	afx_msg void OnSaveNote();
	afx_msg void OnDestroy();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	int m_cnt;
	CString* m_List;
	afx_msg void OnCallList();
};


DWORD CALLBACK MEditStreamInCallback(DWORD_PTR dwCookie, LPBYTE pbBuff, LONG cb, LONG *pcb);
DWORD CALLBACK MEditStreamOutCallback(DWORD_PTR dwCookie, LPBYTE pbBuff, LONG cb, LONG *pcb);
