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
	puts("Hello World!");
	return EXIT_SUCCESS;
}

int RunTests()
{
	puts("Unit testing...");
	// testing::InitGoogleTest(NULL, NULL);
	// return RUN_ALL_TESTS();
	return 0;
}

/*
TEST(Test4Test, SimpleAssertion)
{
	// EXPECT_EQ(1, 2-1);
};
*/
