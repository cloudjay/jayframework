#include "SampleTable.h"
#include <wchar.h>

//---------------------------------------
// SampleItem
//---------------------------------------

int SampleItem::SetValue(const wstring& field, const wstring& value)
{
	const wchar_t* pField = field.c_str();
#ifdef CYGWIN
	if (!wcscasecmp(pField, L"name")) {
#else
	if (!_wcsicmp(pField, L"name")) {
#endif
		name = value;
		return 0;
	}
#ifdef CYGWIN
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
// SampleTable
//---------------------------------------

HREC SampleTable::CreateRecord()
{
	SampleItem *pRec = new SampleItem;
	AddToCache(pRec);
	return pRec;
}

#ifdef UNITTEST
TEST(SampleTable)
{
	SampleTable sampleTable;
	HREC rec = sampleTable.CreateRecord();
	sampleTable.AddField(rec, wstring(L"name"), wstring(L"apple"));
	sampleTable.AddField(rec, wstring(L"price"), wstring(L"1000"));
	CHECK_EQUAL(1, sampleTable.GetCachedHandleCount());

	sampleTable.AddRecord(rec);
	CHECK_EQUAL(1, sampleTable.GetRecCount());
	CHECK_EQUAL(0, sampleTable.GetCachedHandleCount());
}

#include "TableLoader.h"
TEST(LoadSampleTable)
{
	TableLoader	loader;
	SampleTable	table;
	table.SetFileName(L"Sample.xml");
	CHECK(loader.Load(&table));
#ifdef EXPAT
	CHECK_EQUAL(2, table.GetRecCount());
#endif
	SampleTable	table2;
	table2.SetFileName(L"Sample2.xml");
	CHECK(loader.Load(&table2));
#ifdef EXPAT
	CHECK_EQUAL(2, table2.GetRecCount());
#endif
}
#endif
