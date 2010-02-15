/**	\file	define.h
	\brief	Define features
*/

/** \brief Lua */
#define LUA

/** \brief EXPAT SAX XML Parser */
#ifndef __CYGWIN
#define EXPAT
#endif
#ifdef  EXPAT
#define XML_STATIC
#endif

/** \brief UnitTest++ */
#define UNITTEST

/** \brief SQLite */
#define SQLITE
