// NoteArea.cpp : 구현 파일입니다.
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


// CNoteArea 진단입니다.

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


// CNoteArea 메시지 처리기입니다.
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

	// TODO:  여기에 특수화된 작성 코드를 추가합니다.


	return 0;
}

void CNoteArea::OnInitialUpdate()
{
	CRichEditView::OnInitialUpdate();

	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.

	
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

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
}

BOOL CNoteArea::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.



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

		//단락이동.
		if (pMsg->wParam == VK_TAB &&pMsg->hwnd == GetRichEditCtrl().m_hWnd)//탭키 관련
		{
			if (GetKeyState(VK_CONTROL) & 0x8000)//ctrl+tab 일때 단락 이동
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
		//글머리표(동그라미)
		else if (pMsg->wParam == 'u' || pMsg->wParam == 'U'&&pMsg->hwnd == GetRichEditCtrl().m_hWnd)
		{
			if (GetKeyState(VK_CONTROL) & 0x8000)
			{
				m_setting->m_diagram = 1;
				PARAFORMAT2 pf;
				pf.cbSize = sizeof(PARAFORMAT2);
				pf.dwMask = PFM_NUMBERING | PFM_OFFSET | PFM_OFFSETINDENT;
				pf.wNumbering = PFN_BULLET; //글머리표 만들어주는거.
				pf.dxStartIndent = 0;
				pf.dxOffset = 0;
				VERIFY(GetRichEditCtrl().SetParaFormat(pf));
			}
		}
		//글머리표 숫자.
		else if (pMsg->wParam == 'i' || pMsg->wParam == 'I'&&pMsg->hwnd == GetRichEditCtrl().m_hWnd)
		{
			if (GetKeyState(VK_CONTROL) & 0x8000)
			{
				m_setting->m_diagram = 2;
				PARAFORMAT2 pf;
				pf.cbSize = sizeof(PARAFORMAT2);
				pf.dwMask = PFM_NUMBERING | PFM_OFFSET | PFM_OFFSETINDENT;
				pf.wNumbering = PFN_ARABIC; //글머리표 만들어주는거.
				pf.dxStartIndent = 0;
				pf.dxOffset = 0;
				VERIFY(GetRichEditCtrl().SetParaFormat(pf));
			}
		}
		//복사, 잘라내기, 붙여넣기, 실행취소, 다시실행(순서대로.)
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
		//글자색을 빨간색으로
		else if (pMsg->wParam == 'q' || pMsg->wParam == 'Q'&&pMsg->hwnd == GetRichEditCtrl().m_hWnd)
		{
			if (GetKeyState(VK_CONTROL) & 0x8000)
			{
				COLORREF color;
				m_setting->m_fontColor.SetColor(RGB(255, 0, 0));
				m_setting->OnBnClickedMfccolorbutton1();
			}
		}
		//글자크기 키우기
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
		//글자크기 줄이기
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
		//굵게
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
