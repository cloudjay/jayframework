/**	\file	define.h
	\brief	Define features
*/

/** \brief Lua */
//#define LUA

/** \brief EXPAT SAX XML Parser */
//#define EXPAT

/** \brief For now, these lib files are linked only for Win32 */
#ifdef WIN32

	/** \brief UnitTest++ */
	#define UNITTEST

	/** \brief SQLite */
	#define SQLITE

#endif

#ifdef __CYGWIN__
	#define UNITTEST
	#define SQLITE
#endif
