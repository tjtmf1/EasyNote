#include "stdafx.h"
#include "BookMark.h"


CBookMark::CBookMark()
{
}


CBookMark::~CBookMark()
{
}


CBookMarkList::CBookMarkList()
	:nCount(0)
	, List(NULL)
{
}


CBookMarkList::~CBookMarkList()
{
}

bool CBookMarkList::Open(CString path)
{
	if (List != NULL)
	{
		delete[] List;
		nCount = 0;
	}

	CFile file;
	if (file.Open(path, CFile::modeRead))
	{
		int nLength = file.GetLength();
		char* text = new char[nLength];
		file.Read(text, nLength);

		CString str;
		for (int i = 0; i < nLength; i++)
		{
			CString temp;
			temp.Format(_T("%c"), text[i]);
			str += temp;
		}

		for (int i = 0; i < nLength; i++)
		{
			if (text[i] == '\n')
			{
				nCount++;
			}	
		}
		delete[] text;

		List = new CBookMark[nCount];
		for (int i = 0; i < nCount; i++)
		{
			List[i].start = str.Mid(0, 8);
			str.Delete(0, 9);
			List[i].end = str.Mid(0, 8);
			str.Delete(0, 9);
			List[i].title = str.Mid(0, str.Find('\r'));
			str.Delete(0, str.Find('\n') + 1);
		}
		file.Close();
		return true;
	}
	else
		return false;
}

void CBookMarkList::Save(CString path)
{
	CFile file;
	file.Open(path, CFile::modeCreate | CFile::modeWrite);
	CString str;
	for (int i = 0; i < nCount; i++)
	{
		str += List[i].start + _T(" ");
		str += List[i].end + _T(" ");
		str += List[i].title + _T("\r\n");
	}
	file.Write(str, str.GetLength() * 2);
	file.Close();
}

CBookMark CBookMarkList::GetAt(int index)
{
	return List[index];
}

int CBookMarkList::GetSeconds(int index, int mode)
{
	CString h, m, s, temp;
	switch (mode)
	{
	case START:
		temp = List[index].start;
		break;
	case END:
		temp = List[index].end;
		break;
	}

	h = temp.Mid(0, 2);
	temp.Delete(0, 3);
	m = temp.Mid(0, 2);
	temp.Delete(0, 3);
	s = temp;
	return _ttoi(h) * 3600 + _ttoi(m) * 60 + _ttoi(s);
}

void CBookMarkList::Add(CString s, CString e, CString t)
{
	CBookMark* temp = new CBookMark[nCount];
	for (int i = 0; i < nCount; i++)
	{
		temp[i].start = List[i].start;
		temp[i].end = List[i].end;
		temp[i].title = List[i].title;
	}
	nCount++;
	delete[] List;
	List = new CBookMark[nCount];
	for (int i = 0; i < nCount - 1; i++)
	{
		List[i].start = temp[i].start;
		List[i].end = temp[i].end;
		List[i].title = temp[i].title;
	}
	List[nCount - 1].start = s;
	List[nCount - 1].end = e;
	List[nCount - 1].title = t;
}