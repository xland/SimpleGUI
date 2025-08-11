#include <yoga/Yoga.h>
#include "Element.h"

Element::Element():position(0,0),size(980,800)
{
	node = YGNodeNew();
}
Element::~Element() 
{

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
