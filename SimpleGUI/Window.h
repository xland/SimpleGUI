#pragma once
#include <Windows.h>
#include <string>
#include "quickjs.h"

class Window
{
public:
	Window();	
	static void Register(JSContext* ctx, JSModuleDef* m);
	static JSValue Close(JSContext* ctx, JSValueConst this_val, int argc, JSValueConst* argv);
	static JSValue AddEventListener(JSContext* ctx, JSValueConst this_val, int argc, JSValueConst* argv);
	static LRESULT CALLBACK RouteWindowMessage(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
	LRESULT CALLBACK WindowProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);
	static JSClassID WindowClassId;
	HWND hwnd;
private:
	static JSValue WindowNew(JSContext* ctx, JSValueConst jsThis, int argc, JSValueConst* argv);
	static void WindowFinalizer(JSRuntime* rt, JSValue val);
	void createWindow();
	size_t x{ 100 }, y{ 100 }, w{ 800 }, h{600};
	static std::string className;
};

