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
	int RunTests();
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

#endif /* JAYFRAMEWORK_H_ */
