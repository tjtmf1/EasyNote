
// EasyNote.h : EasyNote ���� ���α׷��� ���� �� ��� ����
//
#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"       // �� ��ȣ�Դϴ�.


// CEasyNoteApp:
// �� Ŭ������ ������ ���ؼ��� EasyNote.cpp�� �����Ͻʽÿ�.
//

class CEasyNoteApp : public CWinApp
{
public:
	CEasyNoteApp();


// �������Դϴ�.
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// �����Դϴ�.

	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CEasyNoteApp theApp;
