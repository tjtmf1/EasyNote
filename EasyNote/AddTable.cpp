// AddTable.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "EasyNote.h"
#include "AddTable.h"
#include "afxdialogex.h"


// CAddTable 대화 상자입니다.

IMPLEMENT_DYNAMIC(CAddTable, CDialog)

CAddTable::CAddTable(CWnd* pParent /*=NULL*/)
	: CDialog(CAddTable::IDD, pParent)
	, m_MainWnd(NULL)
{

}

CAddTable::~CAddTable()
{
}

void CAddTable::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, m_time1);
	DDX_Control(pDX, IDC_EDIT2, m_time2);
	DDX_Control(pDX, IDC_EDIT3, m_time3);
	DDX_Control(pDX, IDC_EDIT4, m_time4);
	DDX_Control(pDX, IDC_SPIN1, m_spin1);
	DDX_Control(pDX, IDC_SPIN2, m_spin2);
	DDX_Control(pDX, IDC_SPIN3, m_spin3);
	DDX_Control(pDX, IDC_SPIN4, m_spin4);
	DDX_Control(pDX, IDC_EDIT5, m_className);
	DDX_Control(pDX, IDC_EDIT6, m_day);
}


BEGIN_MESSAGE_MAP(CAddTable, CDialog)
END_MESSAGE_MAP()


// CAddTable 메시지 처리기입니다.

void CAddTable::OnOK()
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.

	try
	{
		CFile file;

		CString fileName = _T("table.txt");
		CString inputData, data1, data2, data3, pastFile;
		CString time1, time2, time3, time4;

		int dataLength;

		m_time1.GetWindowTextW(time1);
		m_time2.GetWindowTextW(time2);
		m_time3.GetWindowTextW(time3);
		m_time4.GetWindowTextW(time4);

		//read
		if (file.Open(fileName, CFile::modeReadWrite))
		{
			dataLength = file.GetLength();

			char* writeBuffer;
			writeBuffer = new char[dataLength];
			file.Read(writeBuffer, dataLength);

			file.Close();

			if (dataLength > 0)
				pastFile.Format(_T("%s"), writeBuffer);
			else
				pastFile.Format(_T(""));
		}
		else
			pastFile.Format(_T(""));

		//write
		data1.Format(_T("$%s:%s~%s:%s$"), time1, time2, time3, time4);

		m_className.GetWindowTextW(data2);

		m_day.GetWindowTextW(data3);

		inputData = pastFile + data2 + data1 + data3 + _T("@");

		dataLength = (inputData.GetLength() + 1) * 2;

		char* buffer = new char[dataLength];

		memcpy(buffer, (unsigned char*)(LPCTSTR)inputData, sizeof(char) * dataLength);

		//저장 코드
		file.Open(fileName, CFile::modeCreate | CFile::modeWrite);

		file.SeekToEnd();

		file.Write(buffer, dataLength);

		file.Close();
		
		try
		{
			AddToList();
		}
		catch (...)
		{
			MessageBox(_T("리스트 추가 실패."));
		}

		MessageBox(_T("저장에 성공하였습니다."));
	}
	catch (...)
	{
		MessageBox(_T("저장에 실패하였습니다."));
	}

	EndDialog(0);

	CDialog::OnOK();
}


BOOL CAddTable::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.

	UDACCEL incre[] = { 0, 10 };

	m_spin1.SetRange(8, 20);

	m_spin2.SetRange(0, 50);
	m_spin2.SetAccel(1, incre);

	m_spin3.SetRange(8, 20);

	m_spin4.SetRange(0, 50);
	m_spin4.SetAccel(1, incre);

	m_time1.SetWindowTextW(_T("8"));
	m_time3.SetWindowTextW(_T("8"));

	m_MainWnd = (CShowTable*)GetParent();

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

void CAddTable::AddToList()
{
	CString data1, data2, data3;
	CString time1, time2, time3, time4;

	m_time1.GetWindowTextW(time1);
	m_time2.GetWindowTextW(time2);
	m_time3.GetWindowTextW(time3);
	m_time4.GetWindowTextW(time4);

	data1.Format(_T("%s:%s~%s:%s"), time1, time2, time3, time4);

	m_className.GetWindowTextW(data2);

	m_day.GetWindowTextW(data3);

	m_MainWnd->m_list.InsertItem(m_MainWnd->m_listCount, data2, 0);
	m_MainWnd->m_list.SetItemText(m_MainWnd->m_listCount, 1, data3);
	m_MainWnd->m_list.SetItemText(m_MainWnd->m_listCount, 2, data1);
}