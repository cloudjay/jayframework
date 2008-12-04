#include "CCTable.h"

void CCTable::RemoveFromCache(HREC hRec)
{
	HRecList::iterator it = m_cachedHandleList.begin();
	for (; it != m_cachedHandleList.end(); ++it)
	{
		if (*it == hRec)
			break;
	}
	if (it != m_cachedHandleList.end())
		m_cachedHandleList.erase(it);
}

/** Delete cached pointers! */
void CCTable::ClearCache()
{
	HRecList::iterator it = m_cachedHandleList.begin();
	for (; it != m_cachedHandleList.end(); ++it)
		SAFE_DELETE(*it);
	m_cachedHandleList.clear();
}