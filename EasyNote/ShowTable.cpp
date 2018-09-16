// ShowTable.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "EasyNote.h"
#include "ShowTable.h"
#include "afxdialogex.h"


// CShowTable ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(CShowTable, CDialog)

CShowTable::CShowTable(CWnd* pParent /*=NULL*/)
	: CDialog(CShowTable::IDD, pParent)
	, m_selected(-1), m_listCount(0)
{

}

CShowTable::~CShowTable()
{
}

void CShowTable::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_list);
}


BEGIN_MESSAGE_MAP(CShowTable, CDialog)
	ON_BN_CLICKED(IDC_BUTTON1, &CShowTable::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CShowTable::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CShowTable::OnBnClickedButton3)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST1, &CShowTable::OnLvnItemchangedList1)
END_MESSAGE_MAP()


// CShowTable �޽��� ó�����Դϴ�.


BOOL CShowTable::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.

	m_list.InsertColumn(0, _T("����"), LVCFMT_CENTER, 100);
	m_list.InsertColumn(1, _T("����"), LVCFMT_CENTER, 180);
	m_list.InsertColumn(2, _T("�ð�"), LVCFMT_CENTER, 100);

	m_list.SetExtendedStyle(m_list.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);

	m_list.ModifyStyle(LVS_TYPEMASK, LVS_REPORT);

	fill_list();

	return TRUE;  // return TRUE unless you set the focus to a control
	// ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.
}

void CShowTable::fill_list()
{
	CFile file;
	CString fileName = _T("table.txt");

	file.Open(fileName, CFile::modeRead);

	int dataLength = file.GetLength();

	char* writeBuffer;
	writeBuffer = new char[dataLength];
	file.Read(writeBuffer, dataLength);

	file.Close();

	CString data, temp;
	int type = 0;

	for (int i = 0; i < dataLength; i++)
	{
		temp.Format(_T("%c"), writeBuffer[i]);
		if (temp == "$")
		{
			if (type == 0)
			{
				m_list.InsertItem(m_listCount, data, 0);
				data.Format(_T(""));
				type = 1;
			}
			else if (type == 1)
			{
				m_list.SetItemText(m_listCount, 2, data);
				data.Format(_T(""));
				type = 0;
			}
		}
		else if (temp == "@")
		{
			m_list.SetItemText(m_listCount, 1, data);
			data.Format(_T(""));
			m_listCount++;
		}
		else
		{
			data += temp;
		}
	}

	delete writeBuffer;
}

void CShowTable::OnBnClickedButton1()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.

	CAddTable m_dlg;
	m_dlg.DoModal();
}


void CShowTable::OnBnClickedButton2()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.

	if (m_selected != -1)
	{
		CAlterTable m_dlg;
		m_dlg.DoModal();
	}
	else
	{
		MessageBox(_T("����� ������ �ּ���"));
	}
}


void CShowTable::OnBnClickedButton3()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.

	if (m_selected != -1)
	{
		m_list.DeleteItem(m_selected);

		DeleteData();

		m_selected = -1;
	}
}


void CShowTable::OnLvnItemchangedList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	*pResult = 0;

	m_selected = pNMLV->iItem;
}

void CShowTable::DeleteData()
{
	if (m_selected != -1)
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
			else if (temp != m_selected)
			{
				data += str;
			}
		}

		delete writeBuffer;
		char* buffer = new char[dataLength];

		memcpy(buffer, (unsigned char*)(LPCTSTR)data, sizeof(char) * dataLength);

		//���� �ڵ�
		file.Open(fileName, CFile::modeWrite);

		file.SeekToBegin();

		file.Write(buffer, dataLength);

		file.Close();

		delete buffer;
	}
}