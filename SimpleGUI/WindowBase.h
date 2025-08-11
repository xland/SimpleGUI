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
	void paintArea();
private:
	/// <summary>
	/// 窗口的位置
	/// </summary>
	Position position;
	/// <summary>
	/// 窗口的大小，
	/// 无边框窗口大小与Element大小一致
	/// 有边框窗口大小与Element大小不一致，因为有边框窗口大小包含边框和标题栏
	/// </summary>
	Size size;
};

