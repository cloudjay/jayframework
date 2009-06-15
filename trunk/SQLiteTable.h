#pragma once
#include "CCTable.h"

class SQLiteTable : public CCTable, public ITable
{
public:
	SQLiteTable();
	virtual ~SQLiteTable()	{ ClearTable(); }

	//---------------------------------------
	// ISax2dTable
	//---------------------------------------
	virtual HREC		CreateRecord();

	int			Exec(const char* sql);
private:
	int			ClearTable();

	string			m_dbName;
	unsigned short		m_newIndex;
};

class SQLiteItem : public IRec
{
public:
	SQLiteItem(unsigned short index, SQLiteTable* pTable)
				:m_index(index), m_pTable(pTable) {}
	virtual ~SQLiteItem() {}

	//---------------------------------------
	// IRec
	//---------------------------------------
	void	SetValue(const wstring& field, const wstring& value);

private:
	unsigned short		m_index;
	SQLiteTable*		m_pTable;
};
