#ifdef WIN32
#include <windows.h>
#endif
#include "SQLiteTable.h"

//---------------------------------------
// SQLiteTable
//---------------------------------------

#define SQL_LEN		128
#define SAMPLE_TABLE	"SampleTable"
#define CREATE_TABLE	"CREATE TABLE "SAMPLE_TABLE"(idx smallint, name varchar(10), price smallint)"
#define INSERT_RECORD	"INSERT INTO "SAMPLE_TABLE" VALUES(%d, '', 0)"
#define UPDATE_RECORD	"UPDATE "SAMPLE_TABLE" SET %s='%s' WHERE idx=%d"
#define CLEAR_TABLE	"DELETE FROM "SAMPLE_TABLE

SQLiteTable::SQLiteTable()
{
	// Set XML record name for CCTable
	m_desc.recName	= L"item";

	m_dbName	= "SampleDB";
	m_newIndex	= 0;
	Exec(CREATE_TABLE);
}

HREC SQLiteTable::CreateRecord()
{
	char sql[SQL_LEN]	= {0,};
#ifdef WIN32
	sprintf_s(sql, SQL_LEN, INSERT_RECORD, m_newIndex);
#else
	sprintf(sql, INSERT_RECORD, m_newIndex);
#endif
	SQLiteItem* pItem = NULL;
	if (Exec(sql) == SQLITE_OK)
		pItem = new SQLiteItem(m_newIndex++, this);
	if (pItem)
		AddToCache(pItem);
	return pItem;
}

int SQLiteTable::Exec(const char* sql)
{
	sqlite3 *db = NULL;

	// The database is opened for reading and writing,
	// and is creates it if it does not already exist.
	int rc = sqlite3_open(m_dbName.c_str(), &db);
	if (rc)
	{
		sqlite3_close(db);
		return rc;
	}	
	rc = sqlite3_exec(db, sql, NULL, NULL, NULL);
	sqlite3_close(db);
	return rc;
}

int SQLiteTable::ClearTable()
{
	return Exec(CLEAR_TABLE);
}

//---------------------------------------
// SQLiteItem
//---------------------------------------

#define MAX_FIELD_LEN	128
void SQLiteItem::SetValue(const wstring& field, const wstring& value)
{
#ifdef WIN32
	char fieldStr[MAX_FIELD_LEN] = {0,};
	WideCharToMultiByte(CP_UTF8, 0, field.c_str(), field.length(), fieldStr, MAX_FIELD_LEN, 0, 0);

	char valueStr[MAX_FIELD_LEN] = {0,};
	WideCharToMultiByte(CP_UTF8, 0, value.c_str(), value.length(), valueStr, MAX_FIELD_LEN, 0, 0);

	char sql[SQL_LEN] = {0,};
	sprintf_s(sql, SQL_LEN, UPDATE_RECORD, fieldStr, valueStr, m_index);
	m_pTable->Exec(sql);
#else
	// how to convert wstring to UTF-8 ???
#endif
}

#ifdef UNITTEST
TEST(SQLiteTable)
{
	SQLiteTable sqliteTable;
	HREC rec = sqliteTable.CreateRecord();
	CHECK(rec);
	sqliteTable.AddField(rec, wstring(L"name"), wstring(L"babo"));
	sqliteTable.AddField(rec, wstring(L"price"), wstring(L"0"));
	CHECK_EQUAL(1, sqliteTable.GetCachedHandleCount());

	sqliteTable.AddRecord(rec);
	CHECK_EQUAL(1, sqliteTable.GetRecCount());
	CHECK_EQUAL(0, sqliteTable.GetCachedHandleCount());
}

#include "TableLoader.h"
TEST(LoadSqliteTable)
{
	TableLoader	loader;
	SQLiteTable	table;
	table.SetFileName(L"Sample.xml");
	CHECK(loader.Load(&table));
	CHECK_EQUAL(2, table.GetRecCount());
}
#endif
