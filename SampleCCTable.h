#ifndef _SAMPLECCTABLE_H_
#define _SAMPLECCTABLE_H_

#include "CCTable.h"

class SampleCCItem : public IRec
{
public:
	virtual ~SampleCCItem() {}

	//---------------------------------------
	// IRec
	//---------------------------------------
	int		SetValue(const wstring& field, const wstring& value);

	wstring	name;
	int	price;
};

/** \brief Table for sample xml file */
class SampleCCTable : public CCTable
{
public:
	SampleCCTable()				{ m_desc.recName = L"item"; }
	virtual ~SampleCCTable()	{ }

	//---------------------------------------
	// ISax2dTable
	//---------------------------------------
	virtual HREC		CreateRecord();
};

#endif // _SAMPLETABLE_H_
