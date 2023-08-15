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
	void LoadIndexJs();
private:
	JSEnv();
	JSRuntime* rt;
	JSContext* ctx;
};

