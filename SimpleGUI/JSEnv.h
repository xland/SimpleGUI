#pragma once
#include "quickjs.h"
#include "quickjs-libc.h"
class JSEnv
{
public:
	static void Init();
	static JSEnv* Get();
	static int RegModel(JSContext* ctx, JSModuleDef* m);
	~JSEnv();
	static void LoadIndexJs(JSContext* ctx);
private:
	JSEnv();
	JSRuntime* rt;
	JSContext* ctx;
};

