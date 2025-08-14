#pragma once
class Element;
class MouseEvent
{
public:
	MouseEvent(const int& x,const int& y);
	~MouseEvent();
	void setRelativePosition(Element* ele);
public:
	int globalX, globalY, x{ 0 }, y{ 0 };
protected:
private:
};

