#ifndef _TABLEMAPPER_H_
#define _TABLEMAPPER_H_

#include "Windows.h"
#include "SampleTable.h"
#include <map>

typedef std::multimap<int, wstring>			SampleMap;
typedef std::multimap<int, wstring>::const_iterator	SampleMapCItor;

class TableShuffler;

class TableMapper
{
public:
	TableMapper()		{ m_pTable = NULL; m_pShuffler = NULL; }
	virtual ~TableMapper()	{}

	void			SetTable(const CCTable* table)   { m_pTable = table; }
	void			SetShuffler(TableShuffler* shuffler) { m_pShuffler = shuffler; }
	void			Map();
	const unsigned		GetRecCount()			{ return m_map.size(); }
	const SampleMap&	GetMap()			{ return m_map; }

private:
	const CCTable*		m_pTable;
	TableShuffler*		m_pShuffler;

	void			MapItem(const HREC pRec);
	SampleMap		m_map;
};

class TableShuffler
{
public:
	TableShuffler()		 { InitializeCriticalSection(&m_cs); m_count = 0; }
	virtual ~TableShuffler() { DeleteCriticalSection(&m_cs); }

	void			Shuffle(const SampleMap* map);
	const unsigned		GetRecCount()			{ return m_map.size(); }
	const SampleMap&	GetMap()			{ return m_map; }
	const unsigned		GetShuffleCount()		{ return m_count; }

private:
	CRITICAL_SECTION	m_cs;
	SampleMap		m_map;
	unsigned		m_count;
};

typedef	std::map<int, int>		CountMap;
typedef	std::map<int, int>::iterator	CountMapItor;

class TableReducer
{
public:
	TableReducer()		{}
	virtual ~TableReducer() {}

	void			Reduce(const SampleMap& map);
	void			PrintOutput();

private:
	void			Count(int number);
	CountMap		m_countMap;
};
#endif // TABLEMAPPER_H_