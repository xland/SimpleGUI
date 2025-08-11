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
	virtual LRESULT CALLBACK customMsgProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
protected:
	std::unique_ptr<WindowBaseImpl> winImpl;
	std::wstring title;
	bool resizable{ true };
private:
	static LRESULT CALLBACK routeWindowMsg(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
	LRESULT CALLBACK windowMsgProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
private:
};

