#include <yoga/Yoga.h>
#include <include/core/SkFontMgr.h>
#include <include/core/SkFontStyle.h>
#include <include/ports/SkTypeface_win.h>
#include <include/core/SkFont.h>
#include <include/core/SkPaint.h>
#include <include/core/SkCanvas.h>
#include "FontManager.h"

#include "Label.h"

namespace {
    static YGSize measureWidget(YGNodeConstRef node, float width, YGMeasureMode widthMode, float height, YGMeasureMode heightMode) {
        auto text = static_cast<Label*>(YGNodeGetContext(node));
        //float measuredWidth = text->measureWidth();
        //float measuredHeight = text->measureHeight();
        //// 根据 Yoga 的约束模式进行裁剪
        //if (widthMode == YGMeasureModeExactly) {
        //    measuredWidth = width;
        //}
        //else if (widthMode == YGMeasureModeAtMost) {
        //    measuredWidth = std::min(measuredWidth, width);
        //}
        //if (heightMode == YGMeasureModeExactly) {
        //    measuredHeight = height;
        //}
        //else if (heightMode == YGMeasureModeAtMost) {
        //    measuredHeight = std::min(measuredHeight, height);
        //}
        return { 100, 100 };
    }
}

Label::Label() {
    YGNodeSetContext(node, this);
    YGNodeSetMeasureFunc(node, &measureWidget);
}
Label::~Label() {

}

void Label::paint(SkCanvas* canvas)
{
    //sk_sp<SkFontMgr> fontMgr = SkFontMgr_New_GDI();
    //SkFontStyle fontStyle = SkFontStyle::Normal();
    //sk_sp<SkTypeface> typeFace = fontMgr->matchFamilyStyle("Microsoft YaHei", fontStyle);
    //SkFont font(typeFace, 56);

    //SkPaint paint;
    //paint.setColor(0xFF00FFFF);
    //canvas->drawString("Hello World!", 20, 120, font, paint);

    SkPaint paint;
    paint.setAntiAlias(true);

    const char* text = "Hello, Bazel world! 测试!!!";
    size_t text_length = strlen(text);

    auto fm = FontManager::get();

    paint.setColor(SK_ColorRED);
    canvas->drawSimpleText(text, text_length, SkTextEncoding::kUTF8, 20, 120, fm->getFont(), paint);
}

void Label::setText(const std::wstring& text)
{
    //如果父容器已经约束住了大小，比如 flex:1 填充满了，Yoga 也不会再问 measureFunc。
    //如果你在 YGNodeStyleSetWidth(node, 100) / YGNodeStyleSetHeight(node, 50) 里已经指定了固定大小，Yoga 就直接用这个值，不会去调用 measureFunc。
    
    //SkRect r;
    //font.measureText(text, text_length, SkTextEncoding::kUTF8, &r);
    this->text = text;
}