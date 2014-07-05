#pragma once
#include "JayFramework.h"

#ifdef V8JS

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

#endif
