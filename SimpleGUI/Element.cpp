#include <yoga/Yoga.h>
#include "include/core/SkRect.h"
#include "include/core/SkCanvas.h"
#include "include/core/SkPaint.h"
#include "Element.h"

Element::Element():position(0,0),size(0,0)
{
	node = YGNodeNew();
}
Element::~Element() 
{
	YGNodeFreeRecursive(node);
}
void Element::addChild(Element* ele)
{
	YGNodeInsertChild(node, ele->node, YGNodeGetChildCount(node));
	children.push_back(ele);
}

void Element::insertChild(const int& index, Element* ele)
{
	YGNodeInsertChild(node, ele->node, index);
	children.insert(children.begin() + index, ele);
}

const std::vector<Element*>& Element::getChildren() 
{
	return children;
}

void Element::setJustifyContent(const Justify& val)
{
	YGNodeStyleSetJustifyContent(node, (YGJustify)val);
}

void Element::setAlignItems(const Align& val)
{
	YGNodeStyleSetAlignItems(node, (YGAlign)val);
}

void Element::setSize(const int& w, const int& h)
{
	YGNodeStyleSetWidth(node, (float)w);
	YGNodeStyleSetHeight(node, (float)h);
	size.w = w;
	size.h = h;
}

void Element::setPosition(const int& x, const int& y)
{
	position.x = x;
	position.y = y;
}

void Element::setBorderWidth(const float& width)
{
	borderWidth = width;
}

void Element::setBorderColor(const Color& color)
{
	borderColor = color;
}

void Element::setBackgroundColor(const Color& color)
{
	bgColor = color;
}

void Element::paint(SkCanvas* canvas)
{
	float x = YGNodeLayoutGetLeft(node);
	float y = YGNodeLayoutGetTop(node);  
	float w = YGNodeLayoutGetWidth(node);
	float h = YGNodeLayoutGetHeight(node);
	SkRect rect = SkRect::MakeXYWH(x, y, w, h);

	// 设置填充颜色并绘制背景
	SkPaint fillPaint;
	fillPaint.setColor(bgColor);
	fillPaint.setStyle(SkPaint::kFill_Style);
	canvas->drawRect(rect, fillPaint);

	rect.setXYWH(x + borderWidth / 2, y + borderWidth / 2, w - borderWidth, h - borderWidth);
	SkPaint paint;
	paint.setAntiAlias(true);
	paint.setColor(borderColor);
	paint.setStrokeWidth(borderWidth);
	paint.setStyle(SkPaint::kStroke_Style);
	canvas->drawRect(rect, paint);

	for (size_t i = 0; i < children.size(); i++)
	{
		children[i]->paint(canvas);
	}
}

void Element::setWidth(const int& w)
{
	YGNodeStyleSetWidth(node, (float)w);
}

void Element::setHeight(const int& h)
{
	YGNodeStyleSetHeight(node, (float)h);
}

void Element::setMargin(const int& val)
{
	YGNodeStyleSetMargin(node, YGEdgeAll, (float)val);
}

void Element::setMargin(const int& left, const int& top, const int& right, const int& bottom)
{
	YGNodeStyleSetMargin(node, YGEdgeLeft, (float)left);
	YGNodeStyleSetMargin(node, YGEdgeTop, (float)top);
	YGNodeStyleSetMargin(node, YGEdgeRight, (float)right);
	YGNodeStyleSetMargin(node, YGEdgeBottom, (float)bottom);
}

void Element::setMargin(const Edge& type, const int& val)
{
	YGNodeStyleSetMargin(node, (YGEdge)type, (float)val);
}

void Element::setPadding(const int& val)
{
	YGNodeStyleSetPadding(node, YGEdgeAll, (float)val);
}

void Element::setPadding(const int& left, const int& top, const int& right, const int& bottom)
{
	YGNodeStyleSetPadding(node, YGEdgeLeft, (float)left);
	YGNodeStyleSetPadding(node, YGEdgeTop, (float)top);
	YGNodeStyleSetPadding(node, YGEdgeRight, (float)right);
	YGNodeStyleSetPadding(node, YGEdgeBottom, (float)bottom);
}

void Element::setPadding(const Edge& type, const int& val)
{
	YGNodeStyleSetPadding(node, (YGEdge)type, (float)val);
}

void Element::layout()
{
	YGNodeCalculateLayout(node, size.w, size.h, YGDirectionLTR);
}

const Position& Element::getPosition()
{
	return position;
}

const Size& Element::getSize()
{
	return size;
}
