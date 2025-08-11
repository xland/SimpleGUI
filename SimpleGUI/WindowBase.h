#pragma once
#include <Windows.h>
#include <windowsx.h>
#include <string>
#include <memory>
#include "Element.h"

class WindowBaseImpl;
class WindowBase:public Element
{
public:
	WindowBase();
	~WindowBase();
	void show();
	void moveToScreenCenter();
	void setTitle(const std::wstring& title);
	const std::wstring& getTitle();


	virtual void createNativeWindow() = 0;
public:
	HWND hwnd;
protected:
	const std::wstring& getWinClsName();
protected:
	std::unique_ptr<WindowBaseImpl> winImpl;
	std::wstring title;
private:
	static LRESULT CALLBACK routeWindowMsg(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
	LRESULT CALLBACK windowMsgProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);	
	LRESULT hitTest(int x, int y);
private:
	bool resizable;
};

