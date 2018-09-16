
// EasyNoteView.h : CEasyNoteView Ŭ������ �������̽�
//

#pragma once

class CEasyNoteView : public CView
{
protected: // serialization������ ��������ϴ�.
	CEasyNoteView();
	DECLARE_DYNCREATE(CEasyNoteView)

// Ư���Դϴ�.
public:
	CEasyNoteDoc* GetDocument() const;

// �۾��Դϴ�.
public:

// �������Դϴ�.
public:
	virtual void OnDraw(CDC* pDC);  // �� �並 �׸��� ���� �����ǵǾ����ϴ�.
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// �����Դϴ�.
public:
	virtual ~CEasyNoteView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ������ �޽��� �� �Լ�
protected:
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // EasyNoteView.cpp�� ����� ����
inline CEasyNoteDoc* CEasyNoteView::GetDocument() const
   { return reinterpret_cast<CEasyNoteDoc*>(m_pDocument); }
#endif

