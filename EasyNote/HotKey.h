#pragma once



// CHotKey �� ���Դϴ�.

class CHotKey : public CFormView
{
	DECLARE_DYNCREATE(CHotKey)

protected:
	CHotKey();           // ���� ����⿡ ���Ǵ� protected �������Դϴ�.
	virtual ~CHotKey();

public:
	enum { IDD = IDD_HOTKEY };
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
};


