#include <yoga/Yoga.h>
#include "include/core/SkRect.h"
#include "include/core/SkCanvas.h"
#include "include/core/SkPaint.h"
#include "include/core/SkRRect.h"
#include "Element.h"
#include "WindowBase.h"
#include "App.h"

Element::Element(): node{ YGNodeNewWithConfig(App::get()->getLayoutConfig())  }
{
	//YGNodeNew()
}

Element::~Element() 
{
	YGNodeFreeRecursive(node);
}

Element* Element::getParent()
{
	return parent;
}

void Element::addChild(Element* ele)
{
	ele->parent = this;
	YGNodeInsertChild(node, ele->node, YGNodeGetChildCount(node));
	children.push_back(ele);
}

void Element::insertChild(const int& index, Element* ele)
{
	ele->parent = this;
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

void Element::setFlexDirection(const FlexDirection& flexDirection)
{
	YGNodeStyleSetFlexDirection(node, (YGFlexDirection)flexDirection);
}

void Element::setFlexGrow(const float& val)
{
	YGNodeStyleSetFlexGrow(node, val);
}

void Element::setFlexShrink(const float& val)
{
	YGNodeStyleSetFlexShrink(node, val);
}

void Element::setRadius(float r)
{
	radiusLT = r; radiusRT = r; radiusRB = r; radiusLB = r;
}

void Element::setRadius(float lt, float rt, float rb, float lb)
{
	radiusLT = lt; radiusRT = rt; radiusRB = rb; radiusLB = lb;
}

void Element::setCaption(bool flag)
{
	isCaption = flag;
}

bool Element::getCaption()
{
	return isCaption;
}

void Element::setSize(const float& w, const float& h)
{
	YGNodeStyleSetWidth(node, w);
	YGNodeStyleSetHeight(node, h);
}
void Element::setWidth(const float& w)
{
	YGNodeStyleSetWidth(node, w);
}
void Element::setHeight(const float& h)
{
	YGNodeStyleSetHeight(node, h);
}
void Element::setWidthPercent(const float& percent)
{
	YGNodeStyleSetWidthPercent(node, percent);
}
void Element::setHeightPercent(const float& percent)
{
	YGNodeStyleSetHeightPercent(node, percent);
}
void Element::setSizePercent(const float& w, const float& h)
{
	YGNodeStyleSetWidthPercent(node, w);
	YGNodeStyleSetHeightPercent(node, h);
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

void Element::setMargin(const float& val)
{
	YGNodeStyleSetMargin(node, YGEdgeAll, val);
}

void Element::setMargin(const float& left, const float& top, const float& right, const float& bottom)
{
	YGNodeStyleSetMargin(node, YGEdgeLeft,left);
	YGNodeStyleSetMargin(node, YGEdgeTop,top);
	YGNodeStyleSetMargin(node, YGEdgeRight,right);
	YGNodeStyleSetMargin(node, YGEdgeBottom,bottom);
}

void Element::setMargin(const Edge& type, const float& val)
{
	YGNodeStyleSetMargin(node, (YGEdge)type,val);
}

void Element::setPadding(const float& val)
{
	YGNodeStyleSetPadding(node, YGEdgeAll, val);
}

void Element::setPadding(const float& left, const float& top, const float& right, const float& bottom)
{
	YGNodeStyleSetPadding(node, YGEdgeLeft,left);
	YGNodeStyleSetPadding(node, YGEdgeTop,top);
	YGNodeStyleSetPadding(node, YGEdgeRight,right);
	YGNodeStyleSetPadding(node, YGEdgeBottom,bottom);
}

void Element::setPadding(const Edge& type, const float& val)
{
	YGNodeStyleSetPadding(node, (YGEdge)type,val);
}

void Element::layout(const float& w, const float& h)
{
	YGNodeCalculateLayout(node, w, h, YGDirectionLTR);
	calculateGlobalPos(children);
}

Position Element::getPosition()
{
	float x = YGNodeLayoutGetLeft(node);
	float y = YGNodeLayoutGetTop(node);
	return Position(x,y);
}

Size Element::getSize()
{
	float w = YGNodeLayoutGetWidth(node);
	float h = YGNodeLayoutGetHeight(node);
	return Size(w,h);
}

WindowBase* Element::getWindow()
{
	Element* temp = this;
	while (temp->parent) {
		temp = temp->parent;
	}
	return (WindowBase*)temp;
}

bool Element::hittest(const int& x, const int& y)
{
	float right = YGNodeLayoutGetWidth(node) + globalX;
	float bottom = YGNodeLayoutGetHeight(node) + globalY;
	if (x > globalX && y > globalY && x < right && y < bottom)
	{
		return true;
	}
	return false;
}

void Element::update()
{
	RECT r{ .left{(int)globalX},.top{(int)globalY},
		.right{(int)YGNodeLayoutGetWidth(node) + (int)globalX},
		.bottom{(int)YGNodeLayoutGetHeight(node) + (int)globalY}
	};
	auto hwnd = getWindow()->getHandle();
	InvalidateRect(hwnd, &r, false);
}

void Element::paint(SkCanvas* canvas)
{
	float x = YGNodeLayoutGetLeft(node);
	float y = YGNodeLayoutGetTop(node);
	float w = YGNodeLayoutGetWidth(node);
	float h = YGNodeLayoutGetHeight(node);
	SkRect rect = SkRect::MakeXYWH(x, y, w, h);
	if (bgColor != 0) { //绘制背景
		SkPaint paint;
		paint.setColor(bgColor);
		paint.setStyle(SkPaint::kFill_Style);
		paintRect(canvas, paint, rect);
	}
	if (borderColor != 0 && borderWidth > 0) { //绘制边框
		rect.setXYWH(x + borderWidth / 2, y + borderWidth / 2, w - borderWidth, h - borderWidth);
		SkPaint paint;
		paint.setAntiAlias(true);
		paint.setColor(borderColor);
		paint.setStrokeWidth(borderWidth);
		paint.setStyle(SkPaint::kStroke_Style);
		paintRect(canvas, paint, rect);
	}
	for (size_t i = 0; i < children.size(); i++)
	{
		canvas->save();
		canvas->translate(x, y);
		children[i]->paint(canvas);
		canvas->restore();
	}
}
void Element::paintRect(SkCanvas* canvas, const SkPaint& paint, const SkRect& rect)
{
	if (radiusLT > 0 || radiusRT > 0 || radiusRB > 0 || radiusLB > 0) {
		SkVector radii[4]{ {radiusLT, radiusLT}, {radiusRT, radiusRT}, {radiusRB, radiusRB}, {radiusLB, radiusLB} };
		SkRRect rr;
		rr.setRectRadii(rect, radii);
		canvas->drawRRect(rr, paint);
	}
	else {
		canvas->drawRect(rect, paint);
	}
}

void Element::calculateGlobalPos(const std::vector<Element*>& children)
{
	for (auto& child : children)
	{
		child->globalX = YGNodeLayoutGetLeft(child->node) + child->parent->globalX;
		child->globalY = YGNodeLayoutGetTop(child->node) + child->parent->globalY;
		if (child->children.size() > 0) {
			calculateGlobalPos(child->children);
		}
	}
}

void Element::casecadeShown()
{ 
	//todo hide to show
	shown();
	for (auto& child : children)
	{
		child->casecadeShown();
	}
}
