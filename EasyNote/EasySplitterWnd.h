#pragma once


// CEasySplitterWnd

class CEasySplitterWnd : public CSplitterWnd
{
	DECLARE_DYNAMIC(CEasySplitterWnd)

public:
	CEasySplitterWnd();
	virtual ~CEasySplitterWnd();

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
};


