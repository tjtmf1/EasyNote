#pragma once


// CSetTitle ��ȭ �����Դϴ�.

class CSetTitle : public CDialog
{
	DECLARE_DYNAMIC(CSetTitle)

public:
	CSetTitle(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CSetTitle();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_INSERT_BOOKMARK };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	CString title;
};
