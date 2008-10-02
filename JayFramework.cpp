//============================================================================
// Name        : JayFramework.cpp
// Author      : Jay
// Version     :
// Copyright   : copyleft
// Description : Hello World in C, Ansi-style
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
	return RUN_ALL_TESTS();
}

TEST(Test4Test, SimpleAssertion)
{
	// EXPECT_EQ(1, 2-1);
};
