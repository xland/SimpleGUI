#pragma once
#include <vector>
#include "Align.h"
#include "Justify.h"
#include "Edge.h"
#include "Color.h"
#include "Position.h"
#include "Size.h"

struct YGNode;
class Element
{
public:
	Element();
	~Element();
	void addChild(Element* ele);
	void insertChild(const int& index, Element* ele);
	const std::vector<Element*>& getChildren();
	void setJustifyContent(const Justify& val);
	void setAlignItems(const Align& val);
	void setSize(const int& w, const int& h);
	void setPosition(const int& x, const int& y);
	void setWidth(const int& w);
	void setHeight(const int& h);
	void setMargin(const int& val);
	void setMargin(const int& left, const int& top, const int& right, const int& bottom);
	void setMargin(const Edge& type, const int& val);
	void setPadding(const int& val);
	void setPadding(const int& left, const int& top, const int& right, const int& bottom);
	void setPadding(const Edge& type, const int& val);
	const Position& getPosition();
	const Size& getSize();
public:
	Color bgColor;

protected:
private:
	Position position;
	Size size;
	std::vector<Element*> children;
	YGNode* node;
};

