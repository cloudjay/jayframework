#ifndef _SAMPLETABLE_H_
#define _SAMPLETABLE_H_

#include "CCTable.h"

class SampleItem : public IRec
{
public:
	virtual ~SampleItem() {}

	//---------------------------------------
	// IRec
	//---------------------------------------
	int		SetValue(const wstring& field, const wstring& value);

	wstring	name;
	int	price;
};

/** \brief Table for sample xml file */
class SampleTable : public CCTable, public ITable
{
public:
	SampleTable()		{ m_desc.recName = L"item"; }
	virtual ~SampleTable()	{ }

	//---------------------------------------
	// ISax2dTable
	//---------------------------------------
	virtual HREC		CreateRecord();
};

#endif // _SAMPLETABLE_H_
