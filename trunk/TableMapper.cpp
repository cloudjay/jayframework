#include "TableMapper.h"
#include <assert.h>
#include <process.h>

void TableMapper::StartMapping()
{
	if (m_pTable == NULL)
		return;
	m_map.clear();
	unsigned int count = m_pTable->GetRecCount();
	for (unsigned int i=0; i<count; ++i)
	{
		const SampleItem* pSample = m_pTable->GetNthItem(i);
		if (pSample)
		{
			m_map.insert(std::make_pair(pSample->price, pSample->name));
		}
	}
	if (m_pShuffler)
		m_pShuffler->Shuffle(&m_map);
}

void TableShuffler::Shuffle(const SampleMap* map)
{
	assert(map);
	EnterCriticalSection(&m_cs);
	for (SampleMapCItor it = map->begin(); it != map->end(); ++it)
	{
		m_map.insert(std::make_pair(it->first, it->second));
	}
	LeaveCriticalSection(&m_cs);
}

void TableReducer::Reduce(const SampleMap& map)
{
	for (SampleMapCItor it = map.begin(); it != map.end(); ++it)
	{
		CountMapItor countIt = m_countMap.find(it->first);
		if (countIt != m_countMap.end())
			countIt->second += 1;
		else
			m_countMap.insert(std::make_pair(it->first, 1));
	}
}

#ifdef UNITTEST
#include "TableLoader.h"
SUITE(Mapper)
{

struct SampleMapper
{
	SampleTable	table1;
	SampleTable	table2;
	TableLoader	loader;
	TableMapper	mapper1;
	TableMapper	mapper2;
	TableShuffler	shuffler;

	SampleMapper()
	{
		table1.SetFileName(L"Sample.xml");
		table2.SetFileName(L"Sample2.xml");
		loader.Load(&table1);
		loader.Load(&table2);
		mapper1.SetTable(&table1);
		mapper2.SetTable(&table2);
		mapper1.SetShuffler(&shuffler);
		mapper2.SetShuffler(&shuffler);
	}
};

TEST_FIXTURE(SampleMapper, MapShuffleReduce)
{
	mapper1.StartMapping();
	mapper2.StartMapping();

	TableReducer	reducer;
	reducer.Reduce(shuffler.GetMap());
}

}
#endif // UNITTEST