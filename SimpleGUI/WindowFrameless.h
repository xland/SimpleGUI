#pragma once
#include "WindowBase.h"
class WindowFrameless :public WindowBase
{
public:
	WindowFrameless();
	~WindowFrameless();
public:
protected:
private:
	void setFrameLess();
};

