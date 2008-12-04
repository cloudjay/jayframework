#ifndef _XMLTABLE_H_
#define _XMLTABLE_H_

#include "JayFramework.h"
//
#include <string>
#include <vector>

typedef void*			HREC;
typedef std::vector<HREC>	HRecList;

struct TableDesc {
	string fileName;
	string recName;
};

class ISax2dTable {
public:
	virtual const TableDesc& GetDesc() = 0;
	virtual HREC		CreateRecord() = 0;
	virtual void		AddField(HREC hRec, const string& fieldName, const string& fieldVal) = 0;
	virtual void		AddRecord(HREC hRec) = 0;
};

class ITable {
	virtual unsigned	GetRecCount() = 0;
};

#endif // _XMLTABLE_H_