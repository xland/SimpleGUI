#pragma once

#include <string>
#include "FontSlant.h"
#include "FontWidth.h"
#include "FontWeight.h"

class SkFont;
class FontManager
{
public:
	FontManager();
	~FontManager();
	static void init();
	static FontManager* get();
	SkFont getFont(const std::string& fontName="Microsoft YaHei", 
		const float& fontSize = 13.f,
		const FontWeight& fontWeight=FontWeight::Normal, 
		const FontWidth& fontWidth = FontWidth::Normal, 
		const FontSlant& fontSlant = FontSlant::Upright);
private:
};

