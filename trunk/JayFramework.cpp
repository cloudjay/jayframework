#include <stdio.h>
#include <stdlib.h>
#include "JayFramework.h"
#include "XML.h"

int main(void) {
#ifdef UNITTEST
	RunTests();
#endif
	return EXIT_SUCCESS;
}

#ifdef UNITTEST
/**	\brief Runs all unit tests. */
int RunTests()
{
	puts("Unit testing...");
	return UnitTest::RunAllTests();
}

#ifdef EXPAT
SUITE(ParseSampleXml)
{

struct SampleFixture
{
	FILE*		sampleFile;
	char		xml[MAX_XML_FILE_SIZE];

	SampleFixture() {
		sampleFile = NULL;
#ifdef  __STDC_WANT_SECURE_LIB__
		fopen_s(&sampleFile, "Sample.xml", "r");
#else
		sampleFile = fopen("Sample.xml", "r");
#endif
	}
	~SampleFixture() {
		if (sampleFile)
			fclose(sampleFile);
	}
};

TEST_FIXTURE(SampleFixture, ParserCreate)
{
	XML_Parser parser = XML_ParserCreate(XML_INPUT_INCODING);
	XML_ParserFree(parser);
}

TEST_FIXTURE(SampleFixture, SampleFileExist)
{
	CHECK(sampleFile);
	if (sampleFile)
	{
		int len = fread(xml, sizeof(char), sizeof(xml), sampleFile);
		CHECK(len > 0);
	}
}

TEST_FIXTURE(SampleFixture, ParseSample)
{
	CHECK(sampleFile);
	if (sampleFile == NULL)
		return;

	// Init
	int len = fread(xml, sizeof(char), sizeof(xml), sampleFile);
	XML_Parser parser = XML_ParserCreate(XML_INPUT_INCODING);

	// Parse
	XML_Parse(parser, xml, len, TRUE);

	// Cleanup
	XML_ParserFree(parser);
	if (sampleFile)
		fclose(sampleFile);
}

} // SUITE(ParseSampleXml)
#endif	// EXPAT

#ifdef LUA
TEST(LuaSample)
{
	lua_State *lua = lua_open();
	luaL_openlibs(lua);	// to use io libs in lua
	if (!luaL_loadfile(lua, "Sample.lua"))
		lua_call(lua, 0, 0);
	lua_close(lua);
}
#endif	// LUA

#endif	// UNITTEST
