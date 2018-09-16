
// MainFrm.h : CMainFrame 클래스의 인터페이스
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
	
protected: // serialization에서만 만들어집니다.
	CMainFrame();
	DECLARE_DYNCREATE(CMainFrame)

// 특성입니다.
public:

// 작업입니다.
public:

// 재정의입니다.
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// 구현입니다.
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // 컨트롤 모음이 포함된 멤버입니다.
	CToolBar          m_wndToolBar;
	CStatusBar        m_wndStatusBar;

// 생성된 메시지 맵 함수
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
