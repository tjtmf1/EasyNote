// EasySplitterWnd.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "EasyNote.h"
#include "EasySplitterWnd.h"


// CEasySplitterWnd

IMPLEMENT_DYNAMIC(CEasySplitterWnd, CSplitterWnd)

CEasySplitterWnd::CEasySplitterWnd()
{

}

CEasySplitterWnd::~CEasySplitterWnd()
{
}


BEGIN_MESSAGE_MAP(CEasySplitterWnd, CSplitterWnd)
	ON_WM_RBUTTONDOWN()
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()



// CEasySplitterWnd �޽��� ó�����Դϴ�.




void CEasySplitterWnd::OnRButtonDown(UINT nFlags, CPoint point)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.

	CWnd::OnRButtonDown(nFlags, point);
}


void CEasySplitterWnd::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.

	CSplitterWnd::OnLButtonDown(nFlags, point);
}
