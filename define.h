/**	\file	define.h
	\brief	Define features
*/

/** \brief EXPAT SAX XML Parser */
#define EXPAT

/** \brief Lua */
#define LUA

/** \brief For now, lib files are linked only for Win32 */
#ifdef WIN32
	/** \brief UnitTest++ */
	#define UNITTEST
#endif
