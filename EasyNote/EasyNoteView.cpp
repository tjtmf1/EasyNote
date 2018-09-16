
// EasyNoteView.cpp : CEasyNoteView Ŭ������ ����
//

#include "stdafx.h"
// SHARED_HANDLERS�� �̸� ����, ����� �׸� �� �˻� ���� ó���⸦ �����ϴ� ATL ������Ʈ���� ������ �� ������
// �ش� ������Ʈ�� ���� �ڵ带 �����ϵ��� �� �ݴϴ�.
#ifndef SHARED_HANDLERS
#include "EasyNote.h"
#endif

#include "EasyNoteDoc.h"
#include "EasyNoteView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CEasyNoteView

IMPLEMENT_DYNCREATE(CEasyNoteView, CView)

BEGIN_MESSAGE_MAP(CEasyNoteView, CView)
	// ǥ�� �μ� ����Դϴ�.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
END_MESSAGE_MAP()

// CEasyNoteView ����/�Ҹ�

CEasyNoteView::CEasyNoteView()
{
	// TODO: ���⿡ ���� �ڵ带 �߰��մϴ�.

}

CEasyNoteView::~CEasyNoteView()
{
}

BOOL CEasyNoteView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs�� �����Ͽ� ���⿡��
	//  Window Ŭ���� �Ǵ� ��Ÿ���� �����մϴ�.

	return CView::PreCreateWindow(cs);
}

// CEasyNoteView �׸���

void CEasyNoteView::OnDraw(CDC* /*pDC*/)
{
	CEasyNoteDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: ���⿡ ���� �����Ϳ� ���� �׸��� �ڵ带 �߰��մϴ�.
}


// CEasyNoteView �μ�

BOOL CEasyNoteView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// �⺻���� �غ�
	return DoPreparePrinting(pInfo);
}

void CEasyNoteView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: �μ��ϱ� ���� �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
}

void CEasyNoteView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: �μ� �� ���� �۾��� �߰��մϴ�.
}


// CEasyNoteView ����

#ifdef _DEBUG
void CEasyNoteView::AssertValid() const
{
	CView::AssertValid();
}

void CEasyNoteView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CEasyNoteDoc* CEasyNoteView::GetDocument() const // ����׵��� ���� ������ �ζ������� �����˴ϴ�.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CEasyNoteDoc)));
	return (CEasyNoteDoc*)m_pDocument;
}
#endif //_DEBUG


// CEasyNoteView �޽��� ó����

