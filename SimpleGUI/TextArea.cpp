#include "WindowBase.h"
#include "TextArea.h"

TextArea::TextArea()
{

}

TextArea::~TextArea()
{
}

void TextArea::shown()
{
	Element::shown();
	startFlash();
}

void TextArea::startFlash()
{
	auto hwnd = getWindow()->getHandle();
	SetTimer(hwnd, FlashTimer, 600, NULL); //每600毫秒触发一次
	SendMessage(hwnd, WM_TIMER, FlashTimer, 0); //马上触发一次
}
