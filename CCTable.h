#ifndef _CCTABLE_H_
#define _CCTABLE_H_

#include "ITable.h"

/** Table which uses cached handle for SAX parser */
class CCTable : public ISax2dTable
{
public:
	CCTable()			{}
	virtual ~CCTable()		{}

	//---------------------------------------
	// ISax2dTable
	//---------------------------------------
	virtual const TableDesc&	GetDesc()		{ return m_desc; }
	virtual HREC			CreateRecord()		{ return 0; }
	virtual void			AddField(HREC hRec, const wstring& fieldName, const wstring& fieldVal) {}
	virtual void			AddRecord(HREC hRec)	{}

	void				AddToCache(HREC hRec)	{ m_cachedHandleList.push_back(hRec); }
	unsigned			GetCachedHandleCount()	{ return m_cachedHandleList.size(); }
	void				RemoveFromCache(HREC hRec);
	void				ClearCache();

protected:
	TableDesc			m_desc;
	HRecList			m_cachedHandleList;
};

#endif // _CCTABLE_H_