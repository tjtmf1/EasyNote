// RecordButton.cpp : 구현 파일입니다.
//
//#pragma comment(lib, "winmm")
#include "stdafx.h"
#include "EasyNote.h"
#include "RecordButton.h"
#include <mmsystem.h>
#include "EasyNoteDoc.h"

// CRecordButton

IMPLEMENT_DYNCREATE(CRecordButton, CFormView)

CRecordButton::CRecordButton()
	: CFormView(CRecordButton::IDD)
	, m_bRec(false)
	, m_bPlay(false)
	, m_bBookMark(false)
	, m_playNum(0)
{

}

CRecordButton::~CRecordButton()
{
}

void CRecordButton::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BUTTON1, m_RecButton);
	DDX_Control(pDX, IDC_BUTTON2, m_PlayButton);
}

BEGIN_MESSAGE_MAP(CRecordButton, CFormView)
	ON_BN_CLICKED(IDC_BUTTON1, &CRecordButton::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CRecordButton::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON5, &CRecordButton::OnBnClickedButton5)
END_MESSAGE_MAP()


// CRecordButton 진단입니다.

#ifdef _DEBUG
void CRecordButton::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CRecordButton::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CRecordButton 메시지 처리기입니다.

void CRecordButton::OnBnClickedButton1()
{
	CString string;
	m_RecButton.GetWindowText(string);
	if (!m_bRec)
	{

		((CEasyNoteDoc*)GetDocument())->m_start_time = time(NULL);
		((CEasyNoteDoc*)GetDocument())->m_time_bookmark_start = time(NULL);
		m_bRec = true;
		StartRecordingToFile(((CEasyNoteDoc*)GetDocument())->m_list.nCount);
		m_RecButton.SetWindowText(_T("중지"));
	}
	else
	{
		m_bRec = false;
		AddToBookMark();
		//this->SendMessage(WM_COMMAND, MAKEWPARAM(IDC_BUTTON5, BN_CLICKED));
		m_RecButton.SetWindowText(_T("녹음"));
	}
}


void CRecordButton::OnBnClickedButton2()
{
	CString string;
	m_PlayButton.GetWindowText(string);
	if (!m_bPlay)
	{
		m_bPlay = true;
		StartPlayingFromFile(m_playNum);
		m_PlayButton.SetWindowText(_T("중지"));
	}
	else
	{
		m_bPlay = false;
		StopPlayingFromFile();
		m_PlayButton.SetWindowText(_T("재생"));
		m_playNum++;
	}
}

void CRecordButton::OnEndOfPlayingFile()
{
	m_PlayButton.SetWindowText(_T("재생"));
	m_bPlay = false;
	m_playNum++;
	//StartPlayingFromFile(m_playNum);
	//this->SendMessage(WM_COMMAND, MAKEWPARAM(IDC_BUTTON2, BN_CLICKED));
}

void CRecordButton::OnBnClickedButton5()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	CMainFrame *frame = (CMainFrame*)AfxGetMainWnd();

	if (m_bBookMark == false && m_bRec == true)
	{
		StopRecordingToFile();

		AddToBookMark();
		//doc->m_list.nCount++;

		StartRecordingToFile(((CEasyNoteDoc*)GetDocument())->m_list.nCount);
	}
}

void CRecordButton::AddToBookMark()
{
	CTime ctime = CTime::GetCurrentTime();

	CEasyNoteDoc* doc = (CEasyNoteDoc*)GetDocument();
	CString title;

	if (m_bRec)
	{
		CSetTitle* m_dlg = new CSetTitle();
		if (m_dlg->DoModal() == IDOK)
		{
			title = m_dlg->title;
		}
	}
	else
		title.SetString(_T("finish"));
	

	doc->m_time_bookmark_end = time(NULL);
	int start, end;
	start = doc->m_time_bookmark_start - doc->m_start_time;
	end = doc->m_time_bookmark_end - doc->m_start_time;
	CString str_start, str_end;
	str_start.Format(_T("%02d:%02d:%02d"), (start / 3600), (start % 3600) / 60, (start % 60));
	str_end.Format(_T("%02d:%02d:%02d"), (end / 3600), (end % 3600) / 60, (end % 60));
	doc->m_time_bookmark_start = 0;
	doc->m_time_bookmark_end = 0;
	doc->m_list.Add(str_start, str_end, title);
	CString path;
	path.Format(_T("%02d%02d.txt"), ctime.GetMonth(), ctime.GetDay());
	doc->m_list.Save(path);

	CBookmarkList* dlg = ((CBookmarkList*)(((CMainFrame*)GetParentFrame())->m_RightSplitter.GetPane(1, 0)));
	dlg->m_list.InsertItem(doc->m_list.nCount - 1, doc->m_list.List[doc->m_list.nCount - 1].start, 0);
	dlg->m_list.SetItemText(doc->m_list.nCount - 1, 1, doc->m_list.List[doc->m_list.nCount - 1].end);
	dlg->m_list.SetItemText(doc->m_list.nCount - 1, 2, doc->m_list.List[doc->m_list.nCount - 1].title);

	doc->m_time_bookmark_start = time(NULL);
}

void CRecordButton::OnUpdate(CView* /*pSender*/, LPARAM /*lHint*/, CObject* /*pHint*/)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.


}
