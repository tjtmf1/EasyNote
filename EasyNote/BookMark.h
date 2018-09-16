#pragma once
#define START 0
#define END 1
class CBookMark
{
public:
	CBookMark();
	~CBookMark();
	CString start;
	CString end;
	CString title;
};

class CBookMarkList
{
public:
	CBookMarkList();
	~CBookMarkList();
	CBookMark* List;
	bool Open(CString path);
	void Save(CString path);
	int nCount;
	CBookMark GetAt(int index);
	int GetSeconds(int index, int mode);
	void Add(CString s, CString e, CString t);
};

