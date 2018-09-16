// RichSetting.cpp : ���� �����Դϴ�.
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


// CRichSetting �����Դϴ�.

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


// CRichSetting �޽��� ó�����Դϴ�.

void CRichSetting::OnBnClickedButton1()//��������
{
	m_markPen = true;//������ ��� Ȱ��ȭ
}

void CRichSetting::OnBnClickedButton3()//���ϰ� ���
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

		//�ܶ��̵�.
		if (pMsg->wParam == VK_TAB &&pMsg->hwnd == m_rich->m_hWnd)//��Ű ����
		{
			if (GetKeyState(VK_CONTROL) & 0x8000)//ctrl+tab �϶� �ܶ� �̵�
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
		//�۸Ӹ�ǥ(���׶��)
		else if (pMsg->wParam == 'u' || pMsg->wParam == 'U'&&pMsg->hwnd == m_rich->m_hWnd)
		{
			if (GetKeyState(VK_CONTROL) & 0x8000)
			{
				m_diagram = 1;
				PARAFORMAT2 pf;
				pf.cbSize = sizeof(PARAFORMAT2);
				pf.dwMask = PFM_NUMBERING | PFM_OFFSET | PFM_OFFSETINDENT;
				pf.wNumbering = PFN_BULLET; //�۸Ӹ�ǥ ������ִ°�.
				pf.dxStartIndent = 0;
				pf.dxOffset = 0;
				VERIFY(m_rich->SetParaFormat(pf));
			}
		}
		//�۸Ӹ�ǥ ����.
		else if (pMsg->wParam == 'i' || pMsg->wParam == 'I'&&pMsg->hwnd == m_rich->m_hWnd)
		{
			if (GetKeyState(VK_CONTROL) & 0x8000)
			{
				m_diagram = 2;
				PARAFORMAT2 pf;
				pf.cbSize = sizeof(PARAFORMAT2);
				pf.dwMask = PFM_NUMBERING | PFM_OFFSET | PFM_OFFSETINDENT;
				pf.wNumbering = PFN_ARABIC; //�۸Ӹ�ǥ ������ִ°�.
				pf.dxStartIndent = 0;
				pf.dxOffset = 0;
				VERIFY(m_rich->SetParaFormat(pf));
			}
		}
		//����, �߶󳻱�, �ٿ��ֱ�, �������, �ٽý���(�������.)
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
		//���ڻ��� ����������
		else if (pMsg->wParam == 'q' || pMsg->wParam == 'Q'&&pMsg->hwnd == m_rich->m_hWnd)
		{
			if (GetKeyState(VK_CONTROL) & 0x8000)
			{
				COLORREF color;
				m_fontColor.SetColor(RGB(255, 0, 0));
				OnBnClickedMfccolorbutton1();
			}
		}
		//����ũ�� Ű���
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
		//����ũ�� ���̱�
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
		//����
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


void CRichSetting::OnBnClickedMfccolorbutton1()//���ڻ� 
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
void CRichSetting::OnBnClickedMfccolorbutton2()//���� ����
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

void CRichSetting::OnBnClickedButton6()//�۸Ӹ�ǥ(���׶��)
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
		pf.wNumbering = PFN_BULLET; //�۸Ӹ�ǥ ������ִ°�.
		pf.dxStartIndent = 0;
		pf.dxOffset = 0;
		VERIFY(m_rich->SetParaFormat(pf));
		m_diagram == 1;
	}
}
void CRichSetting::OnBnClickedButton7()//�۸Ӹ�ǥ(i,ii,iii)
{
	m_diagram = 2;
	PARAFORMAT2 pf;
	pf.cbSize = sizeof(PARAFORMAT2);
	pf.dwMask = PFM_NUMBERING | PFM_OFFSET | PFM_OFFSETINDENT;
	pf.wNumbering = PFN_ARABIC; //�۸Ӹ�ǥ ������ִ°�.
	pf.dxStartIndent = -1;
	pf.dxOffset = -1;
	VERIFY(m_rich->SetParaFormat(pf));
}


void CRichSetting::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{

	CFormView::OnKeyDown(nChar, nRepCnt, nFlags);
}

void CRichSetting::OnLButtonUp(UINT nFlags, CPoint point)//���������� �ְ������ �ФФ� �� �̰� �ȸ����� �Ф�
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


void CRichSetting::OnBnClickedButton4()//�ܶ��̵�>>������
{
	PARAFORMAT2 pf;
	pf.cbSize = sizeof(PARAFORMAT2);
	pf.dwMask = PFM_OFFSET | PFM_OFFSETINDENT;
	pf.dxStartIndent = m_tab;
	pf.dxOffset = m_tab;
	VERIFY(m_rich->SetParaFormat(pf));
}

void CRichSetting::OnBnClickedButton5()///�ܶ��̵�<<����
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
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.

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
	// TODO:  RICHEDIT ��Ʈ���� ���, �� ��Ʈ����
	// CFormView::OnInitDialog() �Լ��� ������ 
	//�ϰ� ����ũ�� OR �����Ͽ� ������ ENM_CHANGE �÷��׸� �����Ͽ� CRichEditCtrl().SetEventMask()�� ȣ������ ������
	// �� �˸� �޽����� ������ �ʽ��ϴ�.

	// TODO:  ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	m_count = GetDlgItemInt(IDC_EDIT1);

	/**/
}

int CRichSetting::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFormView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  ���⿡ Ư��ȭ�� �ۼ� �ڵ带 �߰��մϴ�.

	return 0;
}
