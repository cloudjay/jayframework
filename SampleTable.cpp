#include "SampleTable.h"
#include <wchar.h>

//---------------------------------------
// SampleItem
//---------------------------------------

void SampleItem::SetValue(const wstring& field, const wstring& value)
{
	const wchar_t* pField = field.c_str();
	if (!_wcsicmp(pField, L"name")) {
		name = value;
		return;
	}
	if (!_wcsicmp(pField, L"price")) {
		wchar_t* pEnd = NULL;
		price = wcstol(value.c_str(), &pEnd, 10);
		return;
	}
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

void SampleTable::SetFileName(const wchar_t* fileName)
{
	if (fileName)
		m_desc.fileName = fileName;
}

void SampleTable::Clear()
{
	for (HRecItor it = m_list.begin(); it != m_list.end(); ++it)
		SAFE_DELETE(*it);
	m_list.clear();
	ClearCache();
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
	CHECK_EQUAL(2, table.GetRecCount());
	SampleTable	table2;
	table2.SetFileName(L"Sample2.xml");
	CHECK(loader.Load(&table2));
	CHECK_EQUAL(2, table2.GetRecCount());
}
#endif
