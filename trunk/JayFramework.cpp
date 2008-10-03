//============================================================================
// Name        : JayFramework.cpp
// Author      : Jay
// Copyright   : copyleft
//============================================================================

#include <stdio.h>
#include <stdlib.h>
#include "JayFramework.h"

int main(void) {
	RunTests();
	return EXIT_SUCCESS;
}

int RunTests()
{
	puts("Unit testing...");
	return UnitTest::RunAllTests();
}