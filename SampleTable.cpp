#include "SampleTable.h"

HREC SampleTable::CreateRecord()
{
	SampleItem *pRec = new SampleItem;
	AddToCache(pRec);
	return pRec;
}

void SampleTable::AddField(HREC hRec, const wstring &fieldName, const wstring &fieldVal)
{
	SampleItem* pRec = (SampleItem*)hRec;
	const wchar_t* pField = fieldName.c_str();
	if (!_wcsicmp(pField, L"name"))
		pRec->name = fieldVal;
	else if (!_wcsicmp(pField, L"price"))
		pRec->price = _wtoi(fieldVal.c_str());
}

void SampleTable::AddRecord(HREC hRec)
{
	m_table.push_back((SampleItem*)hRec);
	RemoveFromCache(hRec);
}

void SampleTable::Clear()
{
	for (SampleItemVecItor it = m_table.begin(); it != m_table.end(); ++it)
		SAFE_DELETE(*it);
	m_table.clear();
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
	CHECK(loader.Load(&table));
	CHECK_EQUAL(2, table.GetRecCount());	
}
#endif