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
	void	SetValue(const wstring& field, const wstring& value);

// private:
	wstring	name;
	int	price;
};

/** \brief Table for sample xml file */
class SampleTable : public CCTable, public ITable
{
public:
	SampleTable()		{ InitDesc(); }
	virtual ~SampleTable()	{ Clear(); }

	//---------------------------------------
	// ISax2dTable
	//---------------------------------------
	virtual HREC		CreateRecord();

	void			SetFileName(const wchar_t* fileName);

private:
	void			InitDesc() { m_desc.recName = L"item"; }
	void			Clear();
};

#endif // _SAMPLETABLE_H_
