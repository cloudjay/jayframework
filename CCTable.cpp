#include "CCTable.h"
#include <algorithm>

void CCTable::SetFileName(const wchar_t* fileName)
{
	if (fileName)
		m_desc.fileName = fileName;
}

void CCTable::AddRecord(HREC hRec)
{
	m_list.push_back(hRec);
	RemoveFromCache(hRec);
}

void CCTable::AddField(HREC hRec, const wstring &fieldName, const wstring &fieldValue)
{
	hRec->SetValue(fieldName, fieldValue);
}

/** \brief Removes a cached HREC. Doesn't delete that HREC. */
void CCTable::RemoveFromCache(HREC hRec)
{
	HRecList::iterator it = std::find(m_cachedHandleList.begin(), m_cachedHandleList.end(), hRec);
	if (it != m_cachedHandleList.end())
		m_cachedHandleList.erase(it);
}

void CCTable::Clear()
{
	for (HRecItor it = m_list.begin(); it != m_list.end(); ++it)
		SAFE_DELETE(*it);
	m_list.clear();
	ClearCache();
}

/** \brief Clear and delete all cached HRECs. */
void CCTable::ClearCache()
{
	HRecList::iterator it = m_cachedHandleList.begin();
	for (; it != m_cachedHandleList.end(); ++it)
		SAFE_DELETE(*it);
	m_cachedHandleList.clear();
}
