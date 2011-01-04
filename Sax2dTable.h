#pragma once
#include "itable.h"

// Simple sax 2d table
class Sax2dTable : public ISax2dTable
{
public:
	Sax2dTable(void) {}
	virtual ~Sax2dTable(void) {}

	void				SetFileName(const wchar_t* fileName)
						{ if (fileName) m_desc.fileName = fileName; }

	//---------------------------------------
	// ISax2dTable
	//---------------------------------------
	virtual const TableDesc&	GetDesc() const	{ return m_desc; }
	virtual HREC		CreateRecord()			{ return NULL; }
	virtual void		AddField(HREC hRec, const wstring& fieldName, const wstring& fieldVal)
												{ hRec->SetValue(fieldName, fieldVal); }
	virtual void		AddRecord(HREC hRec)	{ m_list.push_back(hRec); }

protected:
	TableDesc			m_desc;
	HRecList			m_list;
};
