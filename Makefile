CXXFLAGS =	-O2 -g -Wall -fmessage-length=0 -I. 

OBJS =		JayFramework.o CCTable.o SampleTable.o

LIBS =		lib/libexpatw.lib

TARGET =	JayFramework.exe

$(TARGET):	$(OBJS)
	$(CXX) -o $(TARGET) $(OBJS) $(LIBS)

all:	$(TARGET)

clean:
	rm -f $(OBJS) $(TARGET)
