#include <include/core/SkFontMgr.h>
#include <include/core/SkFontStyle.h>
#include <include/ports/SkTypeface_win.h>
#include <include/core/SkFont.h>
#include <include/core/SkPaint.h>
#include <include/core/SkCanvas.h>

#include "FontManager.h"

namespace {
	sk_sp<SkFontMgr> fontMgr;
	std::unique_ptr<FontManager> ins;
}


FontManager::FontManager()
{
	fontMgr = SkFontMgr_New_GDI();
}

FontManager::~FontManager()
{
}

void FontManager::init()
{
	ins = std::make_unique<FontManager>();
}

FontManager* FontManager::get()
{
	return ins.get();
}

SkFont FontManager::getFont(const std::string& fontName, 
	const float& fontSize, 
	const FontWeight& fontWeight,
	const FontWidth& fontWidth, 
	const FontSlant& fontSlant)
{
	SkFontStyle fontStyle((SkFontStyle::Weight)fontWeight, (SkFontStyle::Width)fontWidth, (SkFontStyle::Slant)fontSlant);
	sk_sp<SkTypeface> typeFace = fontMgr->matchFamilyStyle(fontName.data(), fontStyle);
	SkFont font(typeFace, fontSize);
	return font;
}