#pragma once
#include <Windows.h>
#include <string>
#include "quickjs.h"

class Window
{
public:	
	static void Register(JSContext* ctx, JSModuleDef* m);

	static JSValue Close(JSContext* ctx, JSValueConst this_val, int argc, JSValueConst* argv);
	void Close();

	static JSValue Show(JSContext* ctx, JSValueConst this_val, int argc, JSValueConst* argv);
	void Show();

	static JSValue AddEventListener(JSContext* ctx, JSValueConst this_val, int argc, JSValueConst* argv);
	static LRESULT CALLBACK RouteWindowMessage(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
	
	LRESULT CALLBACK WindowProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);
	static JSClassID WindowClassId;
	HWND hwnd;
private:
	Window(int x, int y, int width, int height);
	static JSValue WindowNew(JSContext* ctx, JSValueConst jsThis, int argc, JSValueConst* argv);
	static void WindowFinalizer(JSRuntime* rt, JSValue val);
	void createWindow();
	int x, y, width, height;
	static std::string className;
};

