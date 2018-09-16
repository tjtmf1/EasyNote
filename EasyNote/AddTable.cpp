// AddTable.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "EasyNote.h"
#include "AddTable.h"
#include "afxdialogex.h"


// CAddTable ��ȭ �����Դϴ�.

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


// CAddTable �޽��� ó�����Դϴ�.

void CAddTable::OnOK()
{
	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.

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

		//���� �ڵ�
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
			MessageBox(_T("����Ʈ �߰� ����."));
		}

		MessageBox(_T("���忡 �����Ͽ����ϴ�."));
	}
	catch (...)
	{
		MessageBox(_T("���忡 �����Ͽ����ϴ�."));
	}

	EndDialog(0);

	CDialog::OnOK();
}


BOOL CAddTable::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.

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
	// ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.
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