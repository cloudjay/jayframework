/** \file  typedef.h
	\brief common types
*/

#ifndef _WINDEF_
#ifndef BOOL
#define BOOL int
#endif
#endif
#ifndef TRUE
#define TRUE 1
#endif
#ifndef FALSE
#define FALSE 0
#endif

//-----------------------------
// String definition
//-----------------------------
#include <string>
#ifdef __CYGWIN__
namespace std {
	typedef std::basic_string <wchar_t> wstring;
};
#endif
