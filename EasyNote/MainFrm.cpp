
// MainFrm.cpp : CMainFrame Ŭ������ ����
//

#include "stdafx.h"
#include "EasyNote.h"
#include "HotKey.h"
#include "MainFrm.h"
#include "EasyNoteDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	ON_WM_CREATE()
	ON_COMMAND(ID_SHOW_TABLE, &CMainFrame::OnShowTable)
	ON_COMMAND(ID_BOOK_LOAD, &CMainFrame::OnBookLoad)
	ON_COMMAND(ID_32786, &CMainFrame::OnLoadNote)
	ON_COMMAND(ID_32787, &CMainFrame::OnSaveNote)
	ON_WM_DESTROY()
	ON_COMMAND(ID_CALL_LIST, &CMainFrame::OnCallList)
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // ���� �� ǥ�ñ�
	ID_INDICATOR_FILE,
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

// CMainFrame ����/�Ҹ�

CMainFrame::CMainFrame()
	: m_cnt(0)
	, m_List(NULL)
{
	// TODO: ���⿡ ��� �ʱ�ȭ �ڵ带 �߰��մϴ�.
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP | CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("���� ������ ������ ���߽��ϴ�.\n");
		return -1;      // ������ ���߽��ϴ�.
	}

	if (!m_wndStatusBar.Create(this))
	{
		TRACE0("���� ǥ������ ������ ���߽��ϴ�.\n");
		return -1;      // ������ ���߽��ϴ�.
	}
	m_wndStatusBar.SetIndicators(indicators, sizeof(indicators)/sizeof(UINT));

	// TODO: ���� ������ ��ŷ�� �� ���� �Ϸ��� �� �� ���� �����Ͻʽÿ�.
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndToolBar);



	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: CREATESTRUCT cs�� �����Ͽ� ���⿡��
	//  Window Ŭ���� �Ǵ� ��Ÿ���� �����մϴ�.

	cs.cx = 1300;
	cs.cy = 700;

	return TRUE;
}

// CMainFrame ����

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}
#endif //_DEBUG


// CMainFrame �޽��� ó����

BOOL CMainFrame::OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext)
{
	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.

	m_MainSplitter.CreateStatic(this, 1, 3);

	m_MainSplitter.SetColumnInfo(0, 200, 200);

	m_LeftSplitter.CreateStatic(&m_MainSplitter, 2, 1, WS_CHILD | WS_VISIBLE, m_MainSplitter.IdFromRowCol(0, 0));
	m_LeftSplitter.CreateView(0, 0, RUNTIME_CLASS(CNoteList), CSize(200, 400), pContext);
	m_LeftSplitter.CreateView(1, 0, RUNTIME_CLASS(CHotKey), CSize(200, 300), pContext);

	//m_MainSplitter.CreateView(0, 0, RUNTIME_CLASS(CNoteList), CSize(200, 600), pContext);
	//m_MainSplitter.CreateView(0, 1, RUNTIME_CLASS(CNoteArea), CSize(800, 700), pContext);

	m_MainSplitter.SetColumnInfo(1, 800, 200);

	m_CenterSplitter.CreateStatic(&m_MainSplitter, 2, 1, WS_CHILD | WS_VISIBLE, m_MainSplitter.IdFromRowCol(0, 1));
	m_CenterSplitter.CreateView(1, 0, RUNTIME_CLASS(CNoteArea), CSize(200, 600), pContext);
	m_CenterSplitter.CreateView(0, 0, RUNTIME_CLASS(CRichSetting), CSize(200, 150), pContext);
	
	m_RightSplitter.CreateStatic(&m_MainSplitter, 2, 1, WS_CHILD | WS_VISIBLE, m_MainSplitter.IdFromRowCol(0, 2));
	m_RightSplitter.CreateView(0, 0, RUNTIME_CLASS(CRecordButton), CSize(200, 200), pContext);
	m_RightSplitter.CreateView(1, 0, RUNTIME_CLASS(CBookmarkList), CSize(200, 600), pContext);

	//((CRichSetting*)m_CenterSplitter.GetPane(0, 0))->m_rich = &((CNoteArea*)m_CenterSplitter.GetPane(1, 0))->m_rich;

	return true;

	//return CFrameWnd::OnCreateClient(lpcs, pContext);
}

void CMainFrame::OnShowTable()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.

	CShowTable m_dlg;
	m_dlg.DoModal();
}

void CMainFrame::OnBookLoad()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.

	CString path;
	CFileDialog dlg(TRUE);

	if (dlg.DoModal() == IDOK)
	{
		CBookmarkList* m_WndPt = (CBookmarkList*)m_RightSplitter.GetPane(1, 0);

		path = dlg.GetPathName();
		CEasyNoteDoc* doc = ((CEasyNoteDoc*)GetActiveDocument());
		if (doc->m_list.List != NULL)
		{
			delete[] doc->m_list.List;
			doc->m_list.nCount = 0;
		}
		doc->m_list.Open(path);

		m_WndPt->m_list.DeleteAllItems();

		for (int i = 0; i < doc->m_list.nCount; i++)
		{
			m_WndPt->m_list.InsertItem(i, doc->m_list.List[i].start, 0);
			m_WndPt->m_list.SetItemText(i, 1, doc->m_list.List[i].end);
			m_WndPt->m_list.SetItemText(i, 2, doc->m_list.List[i].title);
		}

		m_wndStatusBar.SetPaneText(1, dlg.GetFileName());

		CFileFind find;
		path.Replace(_T(".txt"), _T("00.wav"));

		if (!find.FindFile(path))
		{
			CString message = path;
			message += _T("\n���������� ���������ʽ��ϴ�.");
			AfxMessageBox(message);
		}
		path.Replace(_T(".wav"), _T(".rtf"));
		if (!find.FindFile(path))
		{
			CString message = path;
			message += _T("\n�ʱ������� �������� �ʽ��ϴ�.");
			AfxMessageBox(message);
		}
	}
}


void CMainFrame::OnLoadNote()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.

	CString path;
	CFileDialog dlg(TRUE);

	if (dlg.DoModal() == IDOK)
	{
		CNoteList* m_WndPt = (CNoteList*)m_LeftSplitter.GetPane(0, 0);
		CNoteArea* m_WndPt2 = (CNoteArea*)m_CenterSplitter.GetPane(1, 0);

		path = dlg.GetPathName();

		CFile cFile(path, CFile::modeRead);
		
		EDITSTREAM es;

		es.dwCookie = (DWORD)&cFile;
		es.pfnCallback = MEditStreamInCallback;

		m_WndPt2->GetRichEditCtrl().StreamIn(SF_RTF, es);

		//for (int i = 0; i < m_cnt; i++)
		//	m_WndPt->AddToList(m_List[i], dlg.GetPathName());
		m_WndPt->AddToList(dlg.GetFileName(), dlg.GetPathName());
	}
}

void CMainFrame::OnLoadNoteByPath(CString path)
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.;

	if (path)
	{
		CNoteList* m_WndPt = (CNoteList*)m_LeftSplitter.GetPane(0, 0);
		CNoteArea* m_WndPt2 = (CNoteArea*)m_CenterSplitter.GetPane(1, 0);

		CFile cFile(path, CFile::modeRead);

		EDITSTREAM es;

		es.dwCookie = (DWORD)&cFile;
		es.pfnCallback = MEditStreamInCallback;

		m_WndPt2->GetRichEditCtrl().StreamIn(SF_RTF, es);

		//m_WndPt->AddToList(dlg.GetFileName(), dlg.GetPathName());
	}
}

void CMainFrame::OnSaveNote()
{
	CNoteArea* m_WndPt2 = (CNoteArea*)m_CenterSplitter.GetPane(1, 0);

	CFileDialog dlg(false);

	if (dlg.DoModal() == IDOK)
	{
		CFile cFile;

		cFile.Open(dlg.GetPathName(), CFile::modeCreate | CFile::modeWrite);

		EDITSTREAM es;

		es.dwCookie = (DWORD)&cFile;
		es.pfnCallback = MEditStreamOutCallback;

		m_WndPt2->GetRichEditCtrl().StreamOut(SF_RTF, es); // Perform the streaming
	}
}

static DWORD __stdcall MEditStreamInCallback(DWORD dwCookie, LPBYTE pbBuff, LONG cb, LONG *pcb)
{
	CFile* pFile = (CFile*)dwCookie;

	*pcb = pFile->Read(pbBuff, cb);

	return 0;
}

static DWORD __stdcall MEditStreamOutCallback(DWORD dwCookie, LPBYTE pbBuff, LONG cb, LONG *pcb)
{
	CFile* pFile = (CFile*)dwCookie;

	pFile->Write(pbBuff, cb);
	*pcb = cb;

	return 0;
}

void CMainFrame::OnDestroy()
{
	CFrameWnd::OnDestroy();

	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰��մϴ�.
}

BOOL CMainFrame::PreTranslateMessage(MSG* pMsg)
{
	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.

	if (pMsg->message == WM_KEYDOWN && pMsg->wParam == 'A' && GetKeyState(VK_CONTROL) & 0x8000)
	{
		//��ư ���� �̺�Ʈ �߰�

		m_RightSplitter.GetPane(0, 0)->SendMessage(WM_COMMAND, MAKEWPARAM(IDC_BUTTON5, BN_CLICKED));

		return true;
	}

	return CFrameWnd::PreTranslateMessage(pMsg);
}


void CMainFrame::OnCallList()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.

}
