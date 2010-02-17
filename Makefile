CXXFLAGS =	-O2 -g -Wall -fmessage-length=0 -I. 

SQLITE_OBJS	= sqlite/sqlite3.o
JAY_OBJS	= JayFramework.o CCTable.o SampleTable.o TableLoader.o
LUA_OBJS	= lua/lapi.o lua/lauxlib.o lua/lcode.o lua/ldblib.o lua/ldebug.o lua/ldo.o \
			lua/ldump.o lua/lfunc.o lua/lgc.o lua/linit.o lua/llex.o lua/liolib.o \
			lua/lmathlib.o lua/lmem.o lua/loadlib.o lua/lobject.o lua/lopcodes.o \
			lua/loslib.o lua/lparser.o lua/lstate.o lua/lstring.o lua/lstrlib.o \
			lua/ltable.o lua/ltm.o lua/lundump.o lua/lvm.o lua/lzio.o lua/print.o \
			lua/lbaselib.o lua/ltablib.o
UNITTEST_OBJS = UnitTest++/AssertException.o \
			UnitTest++/Checks.o \
			UnitTest++/CurrentTest.o \
			UnitTest++/DeferredTestReporter.o \
			UnitTest++/DeferredTestResult.o \
			UnitTest++/MemoryOutStream.o \
			UnitTest++/ReportAssert.o \
			UnitTest++/Test.o \
			UnitTest++/TestDetails.o \
			UnitTest++/TestList.o \
			UnitTest++/TestReporter.o \
			UnitTest++/TestReporterStdout.o \
			UnitTest++/TestResults.o \
			UnitTest++/TestRunner.o \
			UnitTest++/TimeConstraint.o \
			UnitTest++/XmlTestReporter.o \
			UnitTest++/Posix/SignalTranslator.o \
			UnitTest++/Posix/TimeHelpers.o

OBJS = $(JAY_OBJS) $(SQLITE_OBJS) $(LUA_OBJS) $(UNITTEST_OBJS)
			
TARGET =	JayFramework.exe

$(TARGET):	$(OBJS)
	$(CXX) -o $(TARGET) $(OBJS) $(LIBS)

all:	$(TARGET)

clean:
	rm -f $(OBJS) $(TARGET)
