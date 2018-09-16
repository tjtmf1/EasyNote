// SetTitle.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "EasyNote.h"
#include "SetTitle.h"
#include "afxdialogex.h"


// CSetTitle 대화 상자입니다.

IMPLEMENT_DYNAMIC(CSetTitle, CDialog)

CSetTitle::CSetTitle(CWnd* pParent /*=NULL*/)
	: CDialog(CSetTitle::IDD, pParent)
	, title(_T(""))
{

}

CSetTitle::~CSetTitle()
{
}

void CSetTitle::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, title);
}


BEGIN_MESSAGE_MAP(CSetTitle, CDialog)
END_MESSAGE_MAP()


// CSetTitle 메시지 처리기입니다.
