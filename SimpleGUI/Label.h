#pragma once

#include <string>
#include "Element.h"

class Label :public Element
{
public:
	Label();
	~Label();
	void paint(SkCanvas* canvas) override;
	void setText(const std::wstring& text);
protected:
	
private:
	std::wstring text;
};

