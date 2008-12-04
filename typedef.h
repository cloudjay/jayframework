/** \file  typedef.h
	\brief common types
*/

#include <string>

/** \brief 문자열은 유니코드만. */
typedef std::wstring string;

#ifndef BOOL
#define BOOL int
#endif
#ifndef TRUE
#define TRUE 1
#endif
#ifndef FALSE
#define FALSE 0
#endif