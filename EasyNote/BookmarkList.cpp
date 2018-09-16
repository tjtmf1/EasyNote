// BookmarkList.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "EasyNote.h"
#include "BookmarkList.h"


// CBookmarkList

IMPLEMENT_DYNCREATE(CBookmarkList, CFormView)

CBookmarkList::CBookmarkList()
	: CFormView(CBookmarkList::IDD)
	, m_item(0)
{

}

CBookmarkList::~CBookmarkList()
{
}

void CBookmarkList::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BOOK_LIST, m_list);
}

BEGIN_MESSAGE_MAP(CBookmarkList, CFormView)
	ON_NOTIFY(NM_DBLCLK, IDC_BOOK_LIST, &CBookmarkList::OnNMDblclkBookList)
END_MESSAGE_MAP()


// CBookmarkList 진단입니다.

#ifdef _DEBUG
void CBookmarkList::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CBookmarkList::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG




void CBookmarkList::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	m_list.InsertColumn(0, _T("시작 시간"), LVCFMT_CENTER, 80);
	m_list.InsertColumn(1, _T("종료 시간"), LVCFMT_CENTER, 80);
	m_list.InsertColumn(2, _T("제목"), LVCFMT_CENTER, 90);

	m_list.SetExtendedStyle(m_list.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);

	m_list.ModifyStyle(LVS_TYPEMASK, LVS_REPORT);


	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
}


void CBookmarkList::OnNMDblclkBookList(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItem = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);

	if (pNMItem->iItem != -1)
	{
		m_item = pNMItem->iItem;
		//StopPlayingFromFile();
		StartPlayingFromFile(m_item);
	}

	*pResult = 0;
}
