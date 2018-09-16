// ShowTable.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "EasyNote.h"
#include "ShowTable.h"
#include "afxdialogex.h"


// CShowTable 대화 상자입니다.

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


// CShowTable 메시지 처리기입니다.


BOOL CShowTable::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.

	m_list.InsertColumn(0, _T("과목"), LVCFMT_CENTER, 100);
	m_list.InsertColumn(1, _T("요일"), LVCFMT_CENTER, 180);
	m_list.InsertColumn(2, _T("시간"), LVCFMT_CENTER, 100);

	m_list.SetExtendedStyle(m_list.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);

	m_list.ModifyStyle(LVS_TYPEMASK, LVS_REPORT);

	fill_list();

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
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
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	CAddTable m_dlg;
	m_dlg.DoModal();
}


void CShowTable::OnBnClickedButton2()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	if (m_selected != -1)
	{
		CAlterTable m_dlg;
		m_dlg.DoModal();
	}
	else
	{
		MessageBox(_T("대상을 선택해 주세요"));
	}
}


void CShowTable::OnBnClickedButton3()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

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
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
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

		//저장 코드
		file.Open(fileName, CFile::modeWrite);

		file.SeekToBegin();

		file.Write(buffer, dataLength);

		file.Close();

		delete buffer;
	}
}