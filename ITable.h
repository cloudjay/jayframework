#ifndef _XMLTABLE_H_
#define _XMLTABLE_H_

#include "JayFramework.h"
#include <vector>

using namespace std;

class IRec {
public:
	virtual int		SetValue(const wstring& field, const wstring& value) = 0;
};

typedef IRec*					 HREC;
typedef vector<HREC>			 HRecList;
typedef HRecList::iterator		 HRecItor;
typedef HRecList::const_iterator HRecCItor;

struct TableDesc {
	wstring fileName;
	wstring recName;
};

class ITable {
};

class ISax2dTable : public ITable {
public:
	virtual const TableDesc& GetDesc() = 0;
	virtual HREC		CreateRecord() = 0;
	virtual void		AddField(HREC hRec, const wstring& fieldName, const wstring& fieldVal) = 0;
	virtual void		AddRecord(HREC hRec) = 0;
};

#endif // _XMLTABLE_H_
