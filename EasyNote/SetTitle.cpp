// SetTitle.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "EasyNote.h"
#include "SetTitle.h"
#include "afxdialogex.h"


// CSetTitle ��ȭ �����Դϴ�.

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


// CSetTitle �޽��� ó�����Դϴ�.
