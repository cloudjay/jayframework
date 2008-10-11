#include <stdio.h>
#include <stdlib.h>
#include "JayFramework.h"

int main(void) {
#ifdef UNITTEST
	RunTests();
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