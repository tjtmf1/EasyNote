// RichSetting.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "EasyNote.h"
#include "RichSetting.h"


// CRichSetting

IMPLEMENT_DYNCREATE(CRichSetting, CFormView)

CRichSetting::CRichSetting()
	: CFormView(CRichSetting::IDD)
	, m_markPen(false)
	, m_bold(false)
	, m_tab(400)
	, m_diagram(0)
	, m_fontRed(false)
	, m_count(18)
{
	m_fontBg.SetColor(RGB(200, 245, 100));
}

CRichSetting::~CRichSetting()
{
}

void CRichSetting::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_MFCCOLORBUTTON1, m_fontColor);
	DDX_Control(pDX, IDC_MFCCOLORBUTTON2, m_fontBg);
	DDX_Control(pDX, IDC_EDIT1, m_fontSize);
	DDX_Control(pDX, IDC_SPIN3, m_spin);
	DDX_Control(pDX, IDC_BUTTON1, m_pen);
}

BEGIN_MESSAGE_MAP(CRichSetting, CFormView)
	ON_BN_CLICKED(IDC_BUTTON1, &CRichSetting::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON3, &CRichSetting::OnBnClickedButton3)
	ON_WM_LBUTTONUP()
	ON_BN_CLICKED(IDC_MFCCOLORBUTTON1, &CRichSetting::OnBnClickedMfccolorbutton1)
	ON_BN_CLICKED(IDC_BUTTON6, &CRichSetting::OnBnClickedButton6)
	ON_BN_CLICKED(IDC_BUTTON7, &CRichSetting::OnBnClickedButton7)
	ON_WM_KEYDOWN()
	ON_BN_CLICKED(IDC_MFCCOLORBUTTON2, &CRichSetting::OnBnClickedMfccolorbutton2)
	ON_BN_CLICKED(IDC_BUTTON4, &CRichSetting::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON5, &CRichSetting::OnBnClickedButton5)
	ON_EN_CHANGE(IDC_EDIT1, &CRichSetting::OnEnChangeEdit1)
	ON_WM_CREATE()
END_MESSAGE_MAP()


// CRichSetting 진단입니다.

#ifdef _DEBUG
void CRichSetting::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CRichSetting::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CRichSetting 메시지 처리기입니다.

void CRichSetting::OnBnClickedButton1()//형광펜기능
{
	m_markPen = true;//형광펜 기능 활성화
}

void CRichSetting::OnBnClickedButton3()//진하게 기능
{
	CHARFORMAT2 cf;
	m_rich->GetSelectionCharFormat(cf);
	if (cf.dwEffects == CFE_BOLD)
	{
		m_bold = false;
	}
	else
	{
		m_bold = true;
	}
	if (m_bold)
	{
		cf.crBackColor = RGB(255, 255, 255);
		cf.dwEffects = CFE_BOLD;
		cf.yHeight = m_count * 10;
		m_rich->SetSelectionCharFormat(cf);
	}
	else
	{
		cf.crBackColor = RGB(255, 255, 255);
		cf.dwEffects = NULL;
		cf.yHeight = m_count * 10;
		m_rich->SetSelectionCharFormat(cf);
	}
}

BOOL CRichSetting::PreTranslateMessage(MSG* pMsg)
{
	if (pMsg->message == WM_KEYDOWN)
	{
		if (GetFocus() != &m_fontSize)
		{
			m_rich->SetFocus();
		}
		CHARFORMAT2 cf;
		m_rich->GetDefaultCharFormat(cf);
		cf.yHeight = m_count * 10;
		cf.crBackColor = RGB(255, 255, 255);
		if (cf.dwEffects == CFE_BOLD)
		{
			m_bold = true;
		}
		else
		{
			m_bold = false;
		}
		if (m_bold)
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
		if (pMsg->wParam == VK_TAB &&pMsg->hwnd == m_rich->m_hWnd)//탭키 관련
		{
			if (GetKeyState(VK_CONTROL) & 0x8000)//ctrl+tab 일때 단락 이동
			{
				pf.dwMask = PFM_OFFSET | PFM_OFFSETINDENT;
				pf.dxStartIndent = m_tab;
				pf.dxOffset = m_tab;
				VERIFY(m_rich->SetParaFormat(pf));
				return true;
			}
			else if (GetKeyState(VK_SHIFT) & 0x8000)
			{
				if (m_tab > 0)
				{
					pf.dwMask = PFM_OFFSET | PFM_OFFSETINDENT;
					pf.dxStartIndent = -m_tab;
					pf.dxOffset = -m_tab;
					VERIFY(m_rich->SetParaFormat(pf));
					return true;
				}
			}
			m_rich->ReplaceSel(_T("\t"));
			return true;
		}
		//글머리표(동그라미)
		else if (pMsg->wParam == 'u' || pMsg->wParam == 'U'&&pMsg->hwnd == m_rich->m_hWnd)
		{
			if (GetKeyState(VK_CONTROL) & 0x8000)
			{
				m_diagram = 1;
				PARAFORMAT2 pf;
				pf.cbSize = sizeof(PARAFORMAT2);
				pf.dwMask = PFM_NUMBERING | PFM_OFFSET | PFM_OFFSETINDENT;
				pf.wNumbering = PFN_BULLET; //글머리표 만들어주는거.
				pf.dxStartIndent = 0;
				pf.dxOffset = 0;
				VERIFY(m_rich->SetParaFormat(pf));
			}
		}
		//글머리표 숫자.
		else if (pMsg->wParam == 'i' || pMsg->wParam == 'I'&&pMsg->hwnd == m_rich->m_hWnd)
		{
			if (GetKeyState(VK_CONTROL) & 0x8000)
			{
				m_diagram = 2;
				PARAFORMAT2 pf;
				pf.cbSize = sizeof(PARAFORMAT2);
				pf.dwMask = PFM_NUMBERING | PFM_OFFSET | PFM_OFFSETINDENT;
				pf.wNumbering = PFN_ARABIC; //글머리표 만들어주는거.
				pf.dxStartIndent = 0;
				pf.dxOffset = 0;
				VERIFY(m_rich->SetParaFormat(pf));
			}
		}
		//복사, 잘라내기, 붙여넣기, 실행취소, 다시실행(순서대로.)
		else if (pMsg->wParam == 'c' || pMsg->wParam == 'C'&&pMsg->hwnd == m_rich->m_hWnd)
		{
			if (GetKeyState(VK_CONTROL) & 0x8000)
			{
				m_rich->Copy();
			}
		}
		else if (pMsg->wParam == 'x' || pMsg->wParam == 'X'&&pMsg->hwnd == m_rich->m_hWnd)
		{
			if (GetKeyState(VK_CONTROL) & 0x8000)
			{
				m_rich->Cut();
			}
		}
		else if (pMsg->wParam == 'v' || pMsg->wParam == 'V'&&pMsg->hwnd == m_rich->m_hWnd)
		{
			if (GetKeyState(VK_CONTROL) & 0x8000)
			{
				if (m_rich->CanPaste()){
					m_rich->Paste();
				}
			}
		}
		else if (pMsg->wParam == 'z' || pMsg->wParam == 'Z'&&pMsg->hwnd == m_rich->m_hWnd)
		{
			if (GetKeyState(VK_CONTROL) & 0x8000)
			{
				if (m_rich->CanUndo())
				{
					m_rich->Undo();
				}
			}
		}
		else if (pMsg->wParam == 'y' || pMsg->wParam == 'Y'&&pMsg->hwnd == m_rich->m_hWnd)
		{
			if (GetKeyState(VK_CONTROL) & 0x8000)
			{
				if (m_rich->CanRedo())
				{
					m_rich->Redo();
				}
			}
		}
		//글자색을 빨간색으로
		else if (pMsg->wParam == 'q' || pMsg->wParam == 'Q'&&pMsg->hwnd == m_rich->m_hWnd)
		{
			if (GetKeyState(VK_CONTROL) & 0x8000)
			{
				COLORREF color;
				m_fontColor.SetColor(RGB(255, 0, 0));
				OnBnClickedMfccolorbutton1();
			}
		}
		//글자크기 키우기
		else if (pMsg->wParam == 'j' || pMsg->wParam == 'J'&&pMsg->hwnd == m_rich->m_hWnd)
		{
			if (GetKeyState(VK_CONTROL) & 0x8000)
			{
				if (m_count + 1 < 100)
				{
					m_count++;
				}
				CHARFORMAT2 cf;
				m_rich->GetDefaultCharFormat(cf);
				cf.yHeight = m_count * 10;
				m_rich->SetSelectionCharFormat(cf);
				m_spin.SetPos(m_count);
			}
		}
		//글자크기 줄이기
		else if (pMsg->wParam == 'k' || pMsg->wParam == 'K'&&pMsg->hwnd == m_rich->m_hWnd)
		{
			if (GetKeyState(VK_CONTROL) & 0x8000)
			{
				if (m_count - 1 > 0)
				{
					m_count--;
				}
				CHARFORMAT2 cf;
				m_rich->GetDefaultCharFormat(cf);
				cf.yHeight = m_count * 10;
				m_rich->SetSelectionCharFormat(cf);
				m_spin.SetPos(m_count);
			}
		}
		//굵게
		else if (pMsg->wParam == 'b' || pMsg->wParam == 'B'&&pMsg->hwnd == m_rich->m_hWnd)
		{
			OnBnClickedButton3();
		}
	}
	if (pMsg->message == WM_LBUTTONUP)
	{
		if (m_markPen&&GetFocus() == m_rich && m_rich->GetSelText().GetLength()>0)
		{
			OnBnClickedMfccolorbutton2();
			m_markPen = false;
		}

	}
	return CFormView::PreTranslateMessage(pMsg);
}


void CRichSetting::OnBnClickedMfccolorbutton1()//글자색 
{
	COLORREF color;
	color = m_fontColor.GetColor();
	CHARFORMAT2 cf;
	m_rich->GetDefaultCharFormat(cf);
	cf.yHeight = m_count * 10;
	cf.crTextColor = color;
	cf.crBackColor = RGB(255, 255, 255);
	if (cf.dwEffects == CFE_BOLD)
	{
		m_bold = true;
	}
	else
	{
		m_bold = false;
	}
	if (m_bold)
	{
		cf.dwEffects = CFE_BOLD;
	}
	else
	{
		cf.dwEffects = NULL;
	}
	cf.yHeight = m_count * 10;
	m_rich->SetSelectionCharFormat(cf);
}
void CRichSetting::OnBnClickedMfccolorbutton2()//글자 배경색
{
	COLORREF bgcolor;
	bgcolor = m_fontBg.GetColor();
	CHARFORMAT2 cf;
	m_rich->GetDefaultCharFormat(cf);
	cf.crBackColor = bgcolor;
	cf.crTextColor = m_fontColor.GetColor();
	if (cf.dwEffects == CFE_BOLD)
	{
		m_bold = true;
	}
	else
	{
		m_bold = false;
	}
	if (m_bold)
	{
		cf.dwEffects = CFE_BOLD;
	}
	else
	{
		cf.dwEffects = NULL;
	}
	cf.yHeight = m_count * 10;
	m_rich->SetSelectionCharFormat(cf);
}

void CRichSetting::OnBnClickedButton6()//글머리표(동그라미)
{
	PARAFORMAT2 pf;
	pf.cbSize = sizeof(PARAFORMAT2);
	if (m_diagram == 1)
	{
		pf.dwMask = PFM_NUMBERING | PFM_OFFSET | PFM_OFFSETINDENT;
		pf.wNumbering = 0;
		pf.dxStartIndent = 0;
		pf.dxOffset = 0;
		VERIFY(m_rich->SetParaFormat(pf));
		m_diagram == 0;

	}
	else
	{

		pf.dwMask = PFM_NUMBERING | PFM_OFFSET | PFM_OFFSETINDENT;
		pf.wNumbering = PFN_BULLET; //글머리표 만들어주는거.
		pf.dxStartIndent = 0;
		pf.dxOffset = 0;
		VERIFY(m_rich->SetParaFormat(pf));
		m_diagram == 1;
	}
}
void CRichSetting::OnBnClickedButton7()//글머리표(i,ii,iii)
{
	m_diagram = 2;
	PARAFORMAT2 pf;
	pf.cbSize = sizeof(PARAFORMAT2);
	pf.dwMask = PFM_NUMBERING | PFM_OFFSET | PFM_OFFSETINDENT;
	pf.wNumbering = PFN_ARABIC; //글머리표 만들어주는거.
	pf.dxStartIndent = -1;
	pf.dxOffset = -1;
	VERIFY(m_rich->SetParaFormat(pf));
}


void CRichSetting::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{

	CFormView::OnKeyDown(nChar, nRepCnt, nFlags);
}

void CRichSetting::OnLButtonUp(UINT nFlags, CPoint point)//형광펜기능을 넣고싶은데 ㅠㅠㅠ 왜 이게 안먹히지 ㅠㅠ
{
	if (m_markPen)
	{
		int len = m_rich->GetSelText().GetLength();
		if (len != 0)
		{
			OnBnClickedMfccolorbutton2();
		}
	}
	PARAFORMAT2 pf;
	CFormView::OnLButtonUp(nFlags, point);
}


void CRichSetting::OnBnClickedButton4()//단락이동>>오른쪽
{
	PARAFORMAT2 pf;
	pf.cbSize = sizeof(PARAFORMAT2);
	pf.dwMask = PFM_OFFSET | PFM_OFFSETINDENT;
	pf.dxStartIndent = m_tab;
	pf.dxOffset = m_tab;
	VERIFY(m_rich->SetParaFormat(pf));
}

void CRichSetting::OnBnClickedButton5()///단락이동<<왼쪽
{
	PARAFORMAT2 pf;
	pf.cbSize = sizeof(PARAFORMAT2);
	if (m_tab > 0)
	{
		pf.dwMask = PFM_OFFSET | PFM_OFFSETINDENT;
		pf.dxStartIndent = -m_tab;
		pf.dxOffset = -m_tab;
		VERIFY(m_rich->SetParaFormat(pf));
	}
}

void CRichSetting::OnCbnSelchangeCombo1()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

}

void CRichSetting::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	m_spin.SetRange(0, 100);
	m_spin.SetPos(m_count);
	m_fontSize.SetWindowTextW(_T("18"));

	m_rich = &((CNoteArea*)((CMainFrame*)GetParentFrame())->m_CenterSplitter.GetPane(1, 0))->GetRichEditCtrl();

	CHARFORMAT2 cf;
	m_rich->GetDefaultCharFormat(cf);
	cf.crBackColor = RGB(255, 255, 255);
	cf.crTextColor = m_fontColor.GetColor();
	cf.dwEffects = NULL;

	cf.yHeight = m_count * 10;
	m_rich->SetSelectionCharFormat(cf);

	m_pen.LoadBitmaps(IDB_BITMAP1);
	
}

void CRichSetting::OnEnChangeEdit1()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CFormView::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
	m_count = GetDlgItemInt(IDC_EDIT1);

	/**/
}

int CRichSetting::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFormView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  여기에 특수화된 작성 코드를 추가합니다.

	return 0;
}
