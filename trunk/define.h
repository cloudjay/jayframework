/**	\file	define.h
	\brief	Define features
*/

/** \brief Lua */
#define LUA

/** \brief EXPAT SAX XML Parser */
#ifndef __CYGWIN__
#define EXPAT
#endif
#ifdef  EXPAT
#define XML_STATIC
#endif

/** \brief UnitTest++ */
#define UNITTEST

/** \brief SQLite */
#define SQLITE

#if defined DLLEXPORT
#define EXPORT extern "C" __declspec(dllexport)
#else
#define EXPORT extern
#endif

#ifdef WIN32
// #define V8JS
#endif
