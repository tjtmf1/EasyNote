// EasySplitterWnd.cpp : 구현 파일입니다.
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



// CEasySplitterWnd 메시지 처리기입니다.




void CEasySplitterWnd::OnRButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	CWnd::OnRButtonDown(nFlags, point);
}


void CEasySplitterWnd::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	CSplitterWnd::OnLButtonDown(nFlags, point);
}
