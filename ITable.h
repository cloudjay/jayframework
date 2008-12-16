#ifndef _XMLTABLE_H_
#define _XMLTABLE_H_

#include "JayFramework.h"

#include <string>
#include <vector>

using namespace std;

typedef void*		HREC;
typedef vector<HREC>	HRecList;

struct TableDesc {
	wstring fileName;
	wstring recName;
};

class ISax2dTable {
public:
	virtual const TableDesc& GetDesc() = 0;
	virtual HREC		CreateRecord() = 0;
	virtual void		AddField(HREC hRec, const wstring& fieldName, const wstring& fieldVal) = 0;
	virtual void		AddRecord(HREC hRec) = 0;
};

class ITable {
	virtual unsigned	GetRecCount() = 0;
};

#endif // _XMLTABLE_H_