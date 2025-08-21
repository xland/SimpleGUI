#include "WindowBase.h"
#include "TextArea.h"

TextArea::TextArea()
{

}

TextArea::~TextArea()
{
}

void TextArea::paint(SkCanvas* canvas)
{

}

void TextArea::shown()
{
	Element::shown();
	startFlash();
}

void TextArea::startFlash()
{
	auto win = getWindow();
	win->focusEle = this;
	auto hwnd = win->getHandle();
	SetTimer(hwnd, FlashCaretTimer, 600, NULL); //每600毫秒触发一次
	SendMessage(hwnd, WM_TIMER, FlashCaretTimer, 0); //马上触发一次
}
