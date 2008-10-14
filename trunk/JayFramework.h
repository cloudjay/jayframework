#ifndef JAYFRAMEWORK_H_
#define JAYFRAMEWORK_H_

#include "define.h"

#ifdef EXPAT
#define  XML_UNICODE_WCHAR_T	// XML Document encoding is UTF-16
#include "expat/expat.h"
#endif

#ifdef UNITTEST
#include "UnitTest++/UnitTest++.h"

int RunTests();
#endif

#endif /* JAYFRAMEWORK_H_ */
