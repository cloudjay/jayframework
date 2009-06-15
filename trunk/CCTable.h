#ifndef _CCTABLE_H_
#define _CCTABLE_H_

#include "ITable.h"

/** Table which uses cached handle for SAX parser */
class CCTable : public ISax2dTable
{
public:
	CCTable()			{}
	virtual ~CCTable()		{ Clear(); }

	void				SetFileName(const wchar_t* fileName);

	//---------------------------------------
	// ISax2dTable
	//---------------------------------------
	virtual const TableDesc&	GetDesc()		{ return m_desc; }
	virtual HREC			CreateRecord()		{ return NULL; }
	virtual void			AddField(HREC hRec, const wstring& fieldName, const wstring& fieldVal);
	virtual void			AddRecord(HREC hRec);

	const unsigned			GetRecCount() const	{ return m_list.size(); }
	HRecCItor			GetBeginCIterator() const { return m_list.begin(); }
	HRecCItor			GetEndCIterator() const	{ return m_list.end(); }

	void				AddToCache(HREC hRec)	{ m_cachedHandleList.push_back(hRec); }
	unsigned			GetCachedHandleCount()	{ return m_cachedHandleList.size(); }
	void				RemoveFromCache(HREC hRec);

protected:
	void				Clear();
	void				ClearCache();

	TableDesc			m_desc;
	HRecList			m_cachedHandleList;
	HRecList			m_list;
};

#endif // _CCTABLE_H_
