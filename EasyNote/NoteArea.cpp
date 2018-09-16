// NoteArea.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "EasyNote.h"
#include "NoteArea.h"
// CNoteArea

IMPLEMENT_DYNCREATE(CNoteArea, CRichEditView)

CNoteArea::CNoteArea()
: CRichEditView()
{
}

CNoteArea::~CNoteArea()
{
}

void CNoteArea::DoDataExchange(CDataExchange* pDX)
{
	CRichEditView::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CNoteArea, CRichEditView)
	ON_WM_DESTROY()
	ON_WM_CREATE()
	ON_WM_SIZE()
END_MESSAGE_MAP()


// CNoteArea �����Դϴ�.

#ifdef _DEBUG
void CNoteArea::AssertValid() const
{
	CRichEditView::AssertValid();
}

#ifndef _WIN32_WCE
void CNoteArea::Dump(CDumpContext& dc) const
{
	CRichEditView::Dump(dc);
}
#endif
#endif //_DEBUG


// CNoteArea �޽��� ó�����Դϴ�.
void CNoteArea::OnDestroy()
{
	// Deactivate the item on destruction; this is important
	// when a splitter view is being used.
	CRichEditView::OnDestroy();
	/*COleClientItem* pActiveItem = GetDocument()->GetInPlaceActiveItem(this);
	if (pActiveItem != NULL && pActiveItem->GetActiveView() == this)
	{
		pActiveItem->Deactivate();
		ASSERT(GetDocument()->GetInPlaceActiveItem(this) == NULL);
	}*/
}


void CNoteArea::ReadData(DWORD_PTR data)
{
	
}

int CNoteArea::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CRichEditView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  ���⿡ Ư��ȭ�� �ۼ� �ڵ带 �߰��մϴ�.


	return 0;
}

void CNoteArea::OnInitialUpdate()
{
	CRichEditView::OnInitialUpdate();

	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.

	
}


void CNoteArea::OnSize(UINT nType, int cx, int cy)
{
	CRichEditView::OnSize(nType, cx, cy);

	/*((CRichSetting*)((CMainFrame*)AfxGetMainWnd())->m_CenterSplitter.GetPane(0, 0))->GetRichEditCtrl() = &GetRichEditCtrl();
	CHARFORMAT2 cf;
	((CRichSetting*)((CMainFrame*)AfxGetMainWnd())->m_CenterSplitter.GetPane(0, 0))->GetRichEditCtrl()->GetDefaultCharFormat(cf);
	cf.crBackColor = RGB(255, 255, 255);
	cf.crTextColor = ((CRichSetting*)((CMainFrame*)AfxGetMainWnd())->m_CenterSplitter.GetPane(0, 0))->m_fontColor.GetColor();
	cf.dwEffects = NULL;

	cf.yHeight = ((CRichSetting*)((CMainFrame*)AfxGetMainWnd())->m_CenterSplitter.GetPane(0, 0))->m_count * 10;
	((CRichSetting*)((CMainFrame*)AfxGetMainWnd())->m_CenterSplitter.GetPane(0, 0))->GetRichEditCtrl()->SetSelectionCharFormat(cf);*/

	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰��մϴ�.
}

BOOL CNoteArea::PreTranslateMessage(MSG* pMsg)
{
	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.



	if (pMsg->message == WM_KEYDOWN)
	{
		m_setting = ((CRichSetting*)((CMainFrame*)GetParentFrame())->m_CenterSplitter.GetPane(0, 0));

		if (GetFocus() != &m_setting->m_fontSize)
		{
			GetRichEditCtrl().SetFocus();
		}
		CHARFORMAT2 cf;
		GetRichEditCtrl().GetDefaultCharFormat(cf);
		cf.yHeight = m_setting->m_count * 10;
		cf.crBackColor = RGB(255, 255, 255);
		if (cf.dwEffects == CFE_BOLD)
		{
			m_setting->m_bold = true;
		}
		else
		{
			m_setting->m_bold = false;
		}
		if (m_setting->m_bold)
		{
			cf.dwEffects = CFE_BOLD;
		}
		else
		{
			cf.dwEffects = NULL;
		}

		PARAFORMAT2 pf;
		pf.cbSize = sizeof(PARAFORMAT2);

		//�ܶ��̵�.
		if (pMsg->wParam == VK_TAB &&pMsg->hwnd == GetRichEditCtrl().m_hWnd)//��Ű ����
		{
			if (GetKeyState(VK_CONTROL) & 0x8000)//ctrl+tab �϶� �ܶ� �̵�
			{
				pf.dwMask = PFM_OFFSET | PFM_OFFSETINDENT;
				pf.dxStartIndent = m_setting->m_tab;
				pf.dxOffset = m_setting->m_tab;
				VERIFY(GetRichEditCtrl().SetParaFormat(pf));
				return true;
			}
			else if (GetKeyState(VK_SHIFT) & 0x8000)
			{
				if (m_setting->m_tab > 0)
				{
					pf.dwMask = PFM_OFFSET | PFM_OFFSETINDENT;
					pf.dxStartIndent = -m_setting->m_tab;
					pf.dxOffset = -m_setting->m_tab;
					VERIFY(GetRichEditCtrl().SetParaFormat(pf));
					return true;
				}
			}
			GetRichEditCtrl().ReplaceSel(_T("\t"));
			return true;
		}
		//�۸Ӹ�ǥ(���׶��)
		else if (pMsg->wParam == 'u' || pMsg->wParam == 'U'&&pMsg->hwnd == GetRichEditCtrl().m_hWnd)
		{
			if (GetKeyState(VK_CONTROL) & 0x8000)
			{
				m_setting->m_diagram = 1;
				PARAFORMAT2 pf;
				pf.cbSize = sizeof(PARAFORMAT2);
				pf.dwMask = PFM_NUMBERING | PFM_OFFSET | PFM_OFFSETINDENT;
				pf.wNumbering = PFN_BULLET; //�۸Ӹ�ǥ ������ִ°�.
				pf.dxStartIndent = 0;
				pf.dxOffset = 0;
				VERIFY(GetRichEditCtrl().SetParaFormat(pf));
			}
		}
		//�۸Ӹ�ǥ ����.
		else if (pMsg->wParam == 'i' || pMsg->wParam == 'I'&&pMsg->hwnd == GetRichEditCtrl().m_hWnd)
		{
			if (GetKeyState(VK_CONTROL) & 0x8000)
			{
				m_setting->m_diagram = 2;
				PARAFORMAT2 pf;
				pf.cbSize = sizeof(PARAFORMAT2);
				pf.dwMask = PFM_NUMBERING | PFM_OFFSET | PFM_OFFSETINDENT;
				pf.wNumbering = PFN_ARABIC; //�۸Ӹ�ǥ ������ִ°�.
				pf.dxStartIndent = 0;
				pf.dxOffset = 0;
				VERIFY(GetRichEditCtrl().SetParaFormat(pf));
			}
		}
		//����, �߶󳻱�, �ٿ��ֱ�, �������, �ٽý���(�������.)
		else if (pMsg->wParam == 'c' || pMsg->wParam == 'C'&&pMsg->hwnd == GetRichEditCtrl().m_hWnd)
		{
			if (GetKeyState(VK_CONTROL) & 0x8000)
			{
				GetRichEditCtrl().Copy();
			}
		}
		else if (pMsg->wParam == 'x' || pMsg->wParam == 'X'&&pMsg->hwnd == GetRichEditCtrl().m_hWnd)
		{
			if (GetKeyState(VK_CONTROL) & 0x8000)
			{
				GetRichEditCtrl().Cut();
			}
		}
		else if (pMsg->wParam == 'v' || pMsg->wParam == 'V'&&pMsg->hwnd == GetRichEditCtrl().m_hWnd)
		{
			if (GetKeyState(VK_CONTROL) & 0x8000)
			{
				if (GetRichEditCtrl().CanPaste()){
					GetRichEditCtrl().Paste();
				}
			}
		}
		else if (pMsg->wParam == 'z' || pMsg->wParam == 'Z'&&pMsg->hwnd == GetRichEditCtrl().m_hWnd)
		{
			if (GetKeyState(VK_CONTROL) & 0x8000)
			{
				if (GetRichEditCtrl().CanUndo())
				{
					GetRichEditCtrl().Undo();
				}
			}
		}
		else if (pMsg->wParam == 'y' || pMsg->wParam == 'Y'&&pMsg->hwnd == GetRichEditCtrl().m_hWnd)
		{
			if (GetKeyState(VK_CONTROL) & 0x8000)
			{
				if (GetRichEditCtrl().CanRedo())
				{
					GetRichEditCtrl().Redo();
				}
			}
		}
		//���ڻ��� ����������
		else if (pMsg->wParam == 'q' || pMsg->wParam == 'Q'&&pMsg->hwnd == GetRichEditCtrl().m_hWnd)
		{
			if (GetKeyState(VK_CONTROL) & 0x8000)
			{
				COLORREF color;
				m_setting->m_fontColor.SetColor(RGB(255, 0, 0));
				m_setting->OnBnClickedMfccolorbutton1();
			}
		}
		//����ũ�� Ű���
		else if (pMsg->wParam == 'j' || pMsg->wParam == 'J'&&pMsg->hwnd == GetRichEditCtrl().m_hWnd)
		{
			if (GetKeyState(VK_CONTROL) & 0x8000)
			{
				if (m_setting->m_count + 1 < 100)
				{
					m_setting->m_count++;
				}
				CHARFORMAT2 cf;
				GetRichEditCtrl().GetDefaultCharFormat(cf);
				cf.yHeight = m_setting->m_count * 10;
				GetRichEditCtrl().SetSelectionCharFormat(cf);
				m_setting->m_spin.SetPos(m_setting->m_count);
			}
		}
		//����ũ�� ���̱�
		else if (pMsg->wParam == 'k' || pMsg->wParam == 'K'&&pMsg->hwnd == GetRichEditCtrl().m_hWnd)
		{
			if (GetKeyState(VK_CONTROL) & 0x8000)
			{
				if (m_setting->m_count - 1 > 0)
				{
					m_setting->m_count--;
				}
				CHARFORMAT2 cf;
				GetRichEditCtrl().GetDefaultCharFormat(cf);
				cf.yHeight = m_setting->m_count * 10;
				GetRichEditCtrl().SetSelectionCharFormat(cf);
				m_setting->m_spin.SetPos(m_setting->m_count);
			}
		}
		//����
		else if (pMsg->wParam == 'b' || pMsg->wParam == 'B'&&pMsg->hwnd == GetRichEditCtrl().m_hWnd)
		{
			m_setting->OnBnClickedButton3();
		}
	}
	if (pMsg->message == WM_LBUTTONUP)
	{
		m_setting = ((CRichSetting*)((CMainFrame*)GetParentFrame())->m_CenterSplitter.GetPane(0, 0));

		if (m_setting->m_markPen && /*GetFocus() == GetRichEditCtrl()&&*/GetRichEditCtrl().GetSelText().GetLength()>0)
		{
			m_setting->OnBnClickedMfccolorbutton2();
			m_setting->m_markPen = false;
		}

	}

	return CRichEditView::PreTranslateMessage(pMsg);
}
