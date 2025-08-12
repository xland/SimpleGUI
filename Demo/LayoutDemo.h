#pragma once

#include <WindowBase.h>
class LayoutDemo
{
public:
	LayoutDemo();
	~LayoutDemo();
	void verticalHorizontalCenter();
	void leftRight();
	void topCenterBottom();
private:
	std::unique_ptr<WindowBase> win;
};

