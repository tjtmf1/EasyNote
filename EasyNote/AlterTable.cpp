// AlterTable.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "EasyNote.h"
#include "AlterTable.h"
#include "afxdialogex.h"


// CAlterTable 대화 상자입니다.

IMPLEMENT_DYNAMIC(CAlterTable, CDialog)

CAlterTable::CAlterTable(CWnd* pParent /*=NULL*/)
: CDialog(CAlterTable::IDD, pParent)
, m_MainWnd(NULL)
{

}

CAlterTable::~CAlterTable()
{
}

void CAlterTable::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT6, m_day);
	DDX_Control(pDX, IDC_EDIT1, m_time1);
	DDX_Control(pDX, IDC_EDIT2, m_time2);
	DDX_Control(pDX, IDC_EDIT3, m_time3);
	DDX_Control(pDX, IDC_EDIT4, m_time4);
	DDX_Control(pDX, IDC_SPIN1, m_spin1);
	DDX_Control(pDX, IDC_SPIN2, m_spin2);
	DDX_Control(pDX, IDC_SPIN3, m_spin3);
	DDX_Control(pDX, IDC_SPIN4, m_spin4);
	DDX_Control(pDX, IDC_EDIT5, m_className);
}


BEGIN_MESSAGE_MAP(CAlterTable, CDialog)
END_MESSAGE_MAP()


// CAlterTable 메시지 처리기입니다.


BOOL CAlterTable::OnInitDialog()
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


void CAlterTable::OnOK()
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.

	try
	{
		DeleteData();

		saveData();

		ChangeLine();

		MessageBox(_T("저장에 성공하였습니다."));
	}
	catch (...)
	{
		MessageBox(_T("저장에 실패하였습니다."));
	}

	EndDialog(0);

	CDialog::OnOK();
}

void CAlterTable::saveData()
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

		pastFile.Format(_T("%s"), writeBuffer);
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

	file.SeekToBegin();

	file.Write(buffer, dataLength);

	file.Close();
}

void CAlterTable::DeleteData()
{	
	int temp = 0;

	CFile file;
	CString fileName = _T("table.txt");

	file.Open(fileName, CFile::modeRead);

	int dataLength = file.GetLength();

	char* writeBuffer;
	writeBuffer = new char[dataLength];
	file.Read(writeBuffer, dataLength);

	file.Close();
	CString data, str;

	for (int i = 0; i < dataLength; i++)
	{
		str.Format(_T("%c"), writeBuffer[i]);
		if (str == "@")
		{
			temp++;
		}
		else if (temp != m_MainWnd->m_selected)
		{
			data += str;
		}
	}

	delete writeBuffer;
	char* buffer = new char[dataLength];

	memcpy(buffer, (unsigned char*)(LPCTSTR)data, sizeof(char) * dataLength);


	//저장 코드
	file.Open(fileName, CFile::modeWrite);

	file.SeekToBegin();

	file.Write(buffer, dataLength);

	file.Close();

	delete buffer;
}

void CAlterTable::ChangeLine()
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

	m_MainWnd->m_list.InsertItem(m_MainWnd->m_selected, data2, 0);
	m_MainWnd->m_list.SetItemText(m_MainWnd->m_selected, 1, data3);
	m_MainWnd->m_list.SetItemText(m_MainWnd->m_selected, 2, data1);

	m_MainWnd->m_list.DeleteItem(m_MainWnd->m_selected + 1);
}