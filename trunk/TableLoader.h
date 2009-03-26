#ifndef _TABLELOADER_H_
#define _TABLELOADER_H_

#include "XML.h"
#include "ITable.h"

class TableWalker {
public:
	ISax2dTable*	pTable;	
	wchar_t		recName[MAX_XML_TAG_NAME_SIZE];
	HREC		curRec;
	wchar_t		curField[MAX_XML_TAG_NAME_SIZE];

	void		OnStartElement  (const XML_Char *name, const XML_Char **atts);
	void		OnEndElement	(const XML_Char *name);

	void		CreateRecord()	{ if (pTable) curRec = pTable->CreateRecord(); }
	void		AddRecord()	{ if (pTable) pTable->AddRecord(curRec); curRec = NULL; }
	void		ClearField()	{ MEMSET_NULL(curField); }
	BOOL		HasCurField()	{ return (pTable && curRec && curField && wcslen(curField)); }
	void		AddField(wchar_t* contents)  { if (pTable) pTable->AddField(curRec, wstring(curField), wstring(contents)); }
};

class TableLoader
{
public:
	TableLoader()		{}
	~TableLoader()		{}

	BOOL			Load(ISax2dTable* table);

private:
#ifdef EXPAT
	BOOL			HandleLoadingError(XML_Error error);

	static void XMLCALL	OnStartElement	(void *userData, const XML_Char *name, const XML_Char **atts);
	static void XMLCALL	OnEndElement	(void *userData, const XML_Char *name);
	static void XMLCALL	OnCharacterData	(void *userData, const XML_Char *s, int len);
#endif
	char			m_xml[MAX_XML_FILE_SIZE];
	TableWalker		m_walker;
};

#endif // _TABLELOADER_H_