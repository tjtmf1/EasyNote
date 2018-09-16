
// EasyNoteDoc.h : CEasyNoteDoc Ŭ������ �������̽�
//


#pragma once
#include "BookmarkList.h"

class CEasyNoteDoc : public CDocument
{
protected: // serialization������ ��������ϴ�.
	
	DECLARE_DYNCREATE(CEasyNoteDoc)

// Ư���Դϴ�.
public:
	CEasyNoteDoc();
// �۾��Դϴ�.
public:

// �������Դϴ�.
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// �����Դϴ�.
public:
	virtual ~CEasyNoteDoc();

	CBookmarkList m_BookmarkList;
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ������ �޽��� �� �Լ�
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// �˻� ó���⿡ ���� �˻� �������� �����ϴ� ����� �Լ�
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
public:
	unsigned long m_start_time;
	unsigned long m_time_bookmark_start;
	unsigned long m_time_bookmark_end;
	CBookMarkList m_list;
	CString m_FileName;
};
