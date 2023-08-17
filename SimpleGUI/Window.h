#pragma once
#include <Windows.h>
#include <string>
#include <vector>
#include "quickjs.h"
#include <blend2d.h>

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
	Window(int x, int y, int width, int height,bool frame,bool shadow,bool visible, bool center,std::wstring title, std::vector<BLBoxI> captionArea);
	static JSValue WindowNew(JSContext* ctx, JSValueConst jsThis, int argc, JSValueConst* argv);
	static void WindowFinalizer(JSRuntime* rt, JSValue val);
	void createWindow();
	int x, y, width, height;
	bool frame, shadow , visible,center;
	std::wstring title;
	static std::string className;
	std::vector<BLBoxI> captionArea;
};

