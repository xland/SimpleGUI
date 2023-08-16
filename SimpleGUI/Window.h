#pragma once
#include <Windows.h>
#include "quickjs.h"

class Window
{
public:
	static void Register(JSContext* ctx, JSModuleDef* m);
	//static JSValue Close(JSContext* ctx, JSValueConst this_val, int argc, JSValueConst* argv);
private:
	
};

