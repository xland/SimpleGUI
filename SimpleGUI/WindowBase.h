#pragma once
#include <Windows.h>
#include <string>

#include "Element.h"
class WindowBase:public Element
{
public:
	WindowBase();
	~WindowBase();
	void createNativeWindow();
	void show();
	void moveToScreenCenter();
	void setTitle(const std::wstring& title);
	const std::wstring& getTitle();
public:
	HWND hwnd;
protected:
protected:
private:
	static LRESULT CALLBACK routeWindowMsg(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
	LRESULT CALLBACK windowMsgProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);	
	LRESULT hitTest(int x, int y);
	const std::wstring& getWinClsName();
private:
	bool resizable;
	std::vector<uint32_t> buffer;
	std::wstring title;
};

