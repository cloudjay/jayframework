#include "SampleCCTable.h"
#include <wchar.h>

//---------------------------------------
// SampleCCItem
//---------------------------------------

int SampleCCItem::SetValue(const wstring& field, const wstring& value)
{
	const wchar_t* pField = field.c_str();
#ifdef __STDC__
	if (!wcscasecmp(pField, L"name")) {
#else
	if (!_wcsicmp(pField, L"name")) {
#endif
		name = value;
		return 0;
	}
#ifdef __STDC__
	if (!wcscasecmp(pField, L"name")) {
#else
	if (!_wcsicmp(pField, L"price")) {
#endif
		wchar_t* pEnd = NULL;
		price = wcstol(value.c_str(), &pEnd, 10);
		return 0;
	}
	return -1;
}

//---------------------------------------
// SampleCCTable
//---------------------------------------

HREC SampleCCTable::CreateRecord()
{
	SampleCCItem *pRec = new SampleCCItem;
	AddToCache(pRec);
	return pRec;
}

#ifdef UNITTEST
TEST(SampleCCTable)
{
	SampleCCTable SampleCCTable;
	HREC rec = SampleCCTable.CreateRecord();
	SampleCCTable.AddField(rec, wstring(L"name"), wstring(L"apple"));
	SampleCCTable.AddField(rec, wstring(L"price"), wstring(L"1000"));
	CHECK_EQUAL(1, SampleCCTable.GetCachedHandleCount());

	SampleCCTable.AddRecord(rec);
	CHECK_EQUAL(1, SampleCCTable.GetRecCount());
	CHECK_EQUAL(0, SampleCCTable.GetCachedHandleCount());
}

#include "TableLoader.h"
TEST(LoadSampleCCTable)
{
	TableLoader	loader;
	SampleCCTable	table;
	table.SetFileName(L"Sample.xml");
#ifdef EXPAT
	CHECK(loader.Load(&table));
	CHECK_EQUAL(2, table.GetRecCount());
#endif
	SampleCCTable	table2;
	table2.SetFileName(L"Sample2.xml");
#ifdef EXPAT
	CHECK(loader.Load(&table2));
	CHECK_EQUAL(2, table2.GetRecCount());
#endif
}
#endif
