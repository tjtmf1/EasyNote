// HotKey.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "EasyNote.h"
#include "HotKey.h"


// CHotKey

IMPLEMENT_DYNCREATE(CHotKey, CFormView)

CHotKey::CHotKey()
	: CFormView(CHotKey::IDD)
{

}

CHotKey::~CHotKey()
{
}

void CHotKey::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CHotKey, CFormView)
END_MESSAGE_MAP()


// CHotKey 진단입니다.

#ifdef _DEBUG
void CHotKey::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CHotKey::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CHotKey 메시지 처리기입니다.
