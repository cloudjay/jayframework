/**	\file	define.h
	\brief	Define features
*/

/**	\brief	For now, lib files are linked only for Win32 */
#ifdef WIN32
/** \brief EXPAT SAX XML Parser */
#define EXPAT
/** \brief UnitTest++ */
#define UNITTEST
/** \brief Lua */
#define LUA
#endif
