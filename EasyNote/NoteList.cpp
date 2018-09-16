// NoteList.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "EasyNote.h"
#include "NoteList.h"


// CNoteList

IMPLEMENT_DYNCREATE(CNoteList, CFormView)

CNoteList::CNoteList()
	: CFormView(CNoteList::IDD)
	, m_listCount(0)
{

}

CNoteList::~CNoteList()
{
}

void CNoteList::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_list);
}

BEGIN_MESSAGE_MAP(CNoteList, CFormView)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST1, &CNoteList::OnLvnItemchangedList1)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST1, &CNoteList::OnNMDblclkList1)
END_MESSAGE_MAP()


// CNoteList 진단입니다.

#ifdef _DEBUG
void CNoteList::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CNoteList::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CNoteList 메시지 처리기입니다.
void CNoteList::AddToList(CString name, CString path)
{
	m_list.InsertItem(m_listCount, name, 0);
	m_list.SetItemText(m_listCount, 1, path);
}

void CNoteList::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	m_list.InsertColumn(0, _T("필기 제목"), LVCFMT_CENTER, 180);

	m_list.SetExtendedStyle(m_list.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);

	m_list.ModifyStyle(LVS_TYPEMASK, LVS_REPORT);


	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
}


void CNoteList::OnLvnItemchangedList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	*pResult = 0;
}


void CNoteList::OnNMDblclkList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItem = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	*pResult = 0;

	if (pNMItem->iItem != -1)
	{
		CString path = m_list.GetItemText(pNMItem->iItem, 0);
		((CMainFrame*)GetParentFrame())->OnLoadNoteByPath(path);
	}
}
