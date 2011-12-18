#ifndef JAYFRAMEWORK_H_
#define JAYFRAMEWORK_H_

#include "define.h"
#include "typedef.h"

#ifdef EXPAT
	#include "expat/expat.h"
#endif

#ifdef UNITTEST
	#include "UnitTest++/UnitTest++.h"
	/** \brief Simple test runner */
	EXPORT int RunTests();
#endif

#ifdef LUA
	#include "lua/lua.hpp"
#endif

#ifndef SAFE_DELETE
#define SAFE_DELETE(x) { if (x) delete x; x = NULL; }
#endif

#ifndef MEMSET_NULL
#define MEMSET_NULL(x) { memset(x, 0x00, sizeof(x)); }
#endif

#ifdef SQLITE
	#include "sqlite/sqlite3.h"
#endif

#ifdef V8JS
	#include "v8/include/v8.h"
#ifdef WIN32
	#undef BOOL
	#include <Windows.h>
	#pragma comment(lib, "winmm.lib")
	#pragma comment(lib, "Ws2_32.lib")
	#pragma warning(disable:4204)
#endif
#endif

#endif /* JAYFRAMEWORK_H_ */
