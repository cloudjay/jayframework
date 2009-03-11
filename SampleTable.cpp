#include "SampleTable.h"
#include <wchar.h>

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
	else if (!_wcsicmp(pField, L"price")) {
		wchar_t* pEnd = NULL;
		pRec->price = wcstol(fieldVal.c_str(), &pEnd, 10);
	}
}

void SampleTable::AddRecord(HREC hRec)
{
	m_table.push_back((SampleItem*)hRec);
	RemoveFromCache(hRec);
}

void SampleTable::SetFileName(const wchar_t* fileName)
{
	if (fileName)
		m_desc.fileName = fileName;
}

const SampleItem* SampleTable::GetNthItem(const unsigned int n) const
{
	if (n<GetRecCount())
	{
		return m_table[n];
	}
	return NULL;
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
	table.SetFileName(L"Sample.xml");
	CHECK(loader.Load(&table));
	CHECK_EQUAL(2, table.GetRecCount());
	SampleTable	table2;
	table2.SetFileName(L"Sample2.xml");
	CHECK(loader.Load(&table2));
	CHECK_EQUAL(2, table2.GetRecCount());
}
#endif
