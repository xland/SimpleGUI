#include "MouseEvent.h"
#include "Element.h"

MouseEvent::MouseEvent(const int& x, const int& y) :globalX{ x }, globalY{y}
{
}

MouseEvent::~MouseEvent()
{
}

void MouseEvent::setRelativePosition(Element* ele)
{
	x = globalX - ele->globalX;
	y = globalY - ele->globalY;
}
