#pragma once
#include "JayFramework.h"

using namespace v8;

class JSRunner
{
public:
	JSRunner(void);
	virtual ~JSRunner(void);

	int Init(const wchar_t* fileName);
	int Run(void);

protected:	
	Persistent<Context>		context;
};

