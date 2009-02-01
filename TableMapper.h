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

	void			SetTable(const SampleTable* table) { m_pTable = table; }
	void			SetShuffler(TableShuffler* shuffler) { m_pShuffler = shuffler; }
	void			StartMapping();
	const unsigned		GetRecCount()			{ return m_map.size(); }
	const SampleMap&	GetMap()			{ return m_map; }

private:
	const SampleTable*	m_pTable;
	SampleMap		m_map;
	TableShuffler*		m_pShuffler;
};

class TableShuffler
{
public:
	TableShuffler()		 { InitializeCriticalSection(&m_cs); }
	virtual ~TableShuffler() { DeleteCriticalSection(&m_cs); }

	void			Shuffle(const SampleMap* map);
	const unsigned		GetRecCount()			{ return m_map.size(); }
	const SampleMap&	GetMap()			{ return m_map; }
private:
	CRITICAL_SECTION	m_cs;
	SampleMap		m_map;
};

typedef	std::map<int, int>		CountMap;
typedef	std::map<int, int>::iterator	CountMapItor;

class TableReducer
{
public:
	TableReducer()		{}
	virtual ~TableReducer() {}

	void			Reduce(const SampleMap& map);

private:
	CountMap		m_countMap;
};
#endif // TABLEMAPPER_H_