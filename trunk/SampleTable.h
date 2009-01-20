#ifndef _SAMPLETABLE_H_
#define _SAMPLETABLE_H_

#include "CCTable.h"

struct SampleItem
{
	wstring	name;
	int	price;
};

typedef std::vector<SampleItem*>		SampleItemVec;
typedef std::vector<SampleItem*>::iterator	SampleItemVecItor;

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
	virtual void		AddField(HREC hRec, const wstring& fieldName, const wstring& fieldVal);
	virtual void		AddRecord(HREC hRec);

	//---------------------------------------
	// ITable
	//---------------------------------------
	unsigned		GetRecCount() { return m_table.size(); }
	void			SetFileName(const wchar_t* fileName);

private:
	void			InitDesc() { m_desc.recName = L"item"; }
	void			Clear();
	SampleItemVec		m_table;
};

#endif // _SAMPLETABLE_H_