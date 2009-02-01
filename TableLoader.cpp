#include "TableLoader.h"
#include <assert.h>
#include <iostream>

/** \brief Parse XML and fill in the table */
BOOL TableLoader::Load(ISax2dTable* table)
{
	assert(table);

	// Check file and record name
	const TableDesc& desc = table->GetDesc();
	if (desc.fileName.length() == 0 ||
		desc.recName.length() == 0)
		return FALSE;

	// Open file
	FILE*	pFile = NULL;
	errno_t	err = _wfopen_s(&pFile, desc.fileName.c_str(), L"r");
	if (pFile == NULL)
		return FALSE;
	int len = fread(m_xml, sizeof(char), sizeof(m_xml), pFile);
	if (len == 0)
		return FALSE;

	// Init table walker
	m_walker.pTable = table;
	wcsncpy_s(m_walker.recName, MAX_XML_TAG_NAME_SIZE, desc.recName.c_str(), desc.recName.length());
	m_walker.curRec = NULL;
	m_walker.ClearField();

#ifdef EXPAT
	// Parse by Expat
	XML_Parser			parser	= XML_ParserCreate(XML_INPUT_INCODING);
	XML_SetUserData			(parser, &m_walker);
	XML_SetElementHandler		(parser, &TableLoader::OnStartElement, &TableLoader::OnEndElement);
	XML_SetCharacterDataHandler	(parser, &TableLoader::OnCharacterData);
	XML_Status status = XML_Parse(parser, m_xml, len, TRUE);
	if (status != XML_STATUS_OK)
	{
		XML_Error error = XML_GetErrorCode(parser);
		switch (error)
		{
		case XML_ERROR_NO_ELEMENTS:
			return TRUE;
		// TODO: report error
		default:
			return FALSE;
		}
	}
#endif
	return TRUE;
}

#ifdef EXPAT
/** \brief Expat start element handler */
void XMLCALL TableLoader::OnStartElement(void *userData, const XML_Char *name, const XML_Char **atts)
{
	assert(userData);
	TableWalker* pWalker = static_cast<TableWalker*>(userData);
	if (pWalker->curRec == NULL)
	{
		if (!_wcsicmp(pWalker->recName, name))
			pWalker->CreateRecord();
	}
	else
	{
		wcsncpy_s(pWalker->curField, MAX_XML_TAG_NAME_SIZE, name, MAX_XML_TAG_NAME_SIZE-1);
	}
#ifdef _DEBUG_MSG
	std::wcout<<L"OnStartElement: "<<name<<L"\n";
#endif
}

/** \brief Expat end element handler */
void XMLCALL TableLoader::OnEndElement(void *userData, const XML_Char *name)
{
	assert(userData);
	TableWalker* pWalker = static_cast<TableWalker*>(userData);
	if (pWalker->pTable)
	{
		if (!_wcsicmp(pWalker->recName, name))
			pWalker->AddRecord();
		if (!_wcsicmp(pWalker->curField, name))
			pWalker->ClearField();
	}
#ifdef _DEBUG_MSG
	std::wcout<<L"OnEndElement:   "<<name<<L"\n";
#endif
}

/** \brief Expat CDATA handler */
void XMLCALL TableLoader::OnCharacterData(void *userData, const XML_Char *s, int len)
{
	assert(userData);
	TableWalker* pWalker = static_cast<TableWalker*>(userData);
	if (pWalker->HasCurField() && s)
	{
		wchar_t	buf[MAX_XML_TAG_NAME_SIZE] = {0,};
		wcsncpy_s(buf, MAX_XML_TAG_NAME_SIZE, s, len);
		pWalker->AddField(buf);
#ifdef _DEBUG_MSG
		std::wcout<<L"OnCDATA: "<<buf<<L"\n";
#endif
	}
}
#endif // EXPAT