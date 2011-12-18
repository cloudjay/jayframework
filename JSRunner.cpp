#include "JSRunner.h"

JSRunner::JSRunner(void)
{
}


JSRunner::~JSRunner(void)
{
	context.Dispose();
}

static Handle<Value> printCallback(const Arguments& args) {
	if (args.Length() < 1)
		return v8::Undefined();
	HandleScope scope;
	Handle<Value> arg = args[0];
	String::Utf8Value value(arg);
	printf(*value);
#if defined (_DEBUG) && defined (WIN32)
	{
		wchar_t wcsMsg[1024] = {0,};
		::MultiByteToWideChar(CP_UTF8, 0, *value, -1, wcsMsg, 1024);
		::OutputDebugStringW(wcsMsg);
	}
#endif
	return v8::Undefined();
}

int JSRunner::Init(const wchar_t* jsFileName)
{
	HandleScope handle_scope;	// Create a handle scope to hold the temporary references.

	// Read file
	FILE* file = _wfopen(jsFileName, L"rb");
	if (file == NULL)
		return -1;
	fseek(file, 0, SEEK_END);
	int size = ftell(file);
	rewind(file);
	char* chars = new char[size + 1];
	chars[size] = L'\0';
	for (int i = 0; i < size;) {
		int read = fread(&chars[i], 1, size-i, file);
		i += read;
	}
	fclose(file);

	// Read script string
	Handle<String> scriptString = String::New(chars, size);
	if (scriptString.IsEmpty())
		return -1;

	// Create a template for the global object where we set the
	// built-in global functions.
	Handle<ObjectTemplate> global = ObjectTemplate::New();
	global->Set(String::New("print"), FunctionTemplate::New(printCallback));

	// Create context
	context = Context::New(NULL, global);
	Context::Scope context_scope(context);	// Enter the context
	TryCatch try_catch;						// Set up an error handler

	// Compile script
	Handle<Script> compiled_script = Script::Compile(scriptString);	
	if (compiled_script.IsEmpty())
	{
		String::Utf8Value error(try_catch.Exception());
#ifdef _DEBUG_MSG
		printf(*error);
#endif
		return -1;
	}

	// Run Initialize() function in JS
	if (compiled_script.IsEmpty())
		return -1;
	Handle<Value> result = compiled_script->Run();
	if (result.IsEmpty()) {
		String::Utf8Value error(try_catch.Exception());
#ifdef _DEBUG_MSG
		printf(*error);
#endif
		return -1;
	}

	return 0;
}

int JSRunner::Run(void)
{
	HandleScope handle_scope;	// Create a handle scope to hold the temporary references.

	// Enter context
	if (context.IsEmpty())
		return -1;
	Context::Scope context_scope(context);

	TryCatch try_catch;			// Set up an error handler

	// Get JS function handle
	Handle<String>	jsFuncName	= String::New("main");
	Handle<Value>	jsFuncVal	= context->Global()->Get(jsFuncName);
	if (!jsFuncVal->IsFunction())
		return -1;
	Handle<Function>	jsFunc	= Handle<Function>::Cast(jsFuncVal);
	// PersistetnFunc = Persistent<Function>::New(jsFunc);

	Handle<Value> result = jsFunc->Call(context->Global(), 0, NULL);
	if (result.IsEmpty()) {
		String::Utf8Value error(try_catch.Exception());
#ifdef _DEBUG_MSG
		printf(*error);
		return -1;
#endif
	}

	return 0;
}
