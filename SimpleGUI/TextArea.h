#pragma once

#include "Element.h"

class TextArea :public Element
{
public:
	TextArea();
	~TextArea();
protected:
	void shown() override;
private:
	void startFlash();
};

