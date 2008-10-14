#include <stdio.h>
#include <stdlib.h>
#include "JayFramework.h"

int main(void) {
#ifdef UNITTEST
	RunTests();
#endif
#ifdef EXPAT
	XML_Char	encoding[] = L"UTF-16";
	XML_Parser	parser = XML_ParserCreate(encoding);
	XML_ParserFree(parser);
#endif
	return EXIT_SUCCESS;
}

#ifdef UNITTEST
int RunTests()
{
	puts("Unit testing...");
	return UnitTest::RunAllTests();
}
#endif
