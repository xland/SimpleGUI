#pragma once
#include "Align.h"
#include "Justify.h"
#include "Edge.h"
#include "Color.h"
#include "Position.h"
#include "Size.h"
#include "FlexDirection.h"
#include "Event.h"

struct YGNode;
struct SkRect;
class SkCanvas;
class SkPaint;
class MouseEvent;
class Element:public Event
{
public:
	Element();
	~Element();
	void addChild(Element* ele);
	Element* getParent();
	void insertChild(const int& index, Element* ele);
	const std::vector<Element*>& getChildren();
	void setJustifyContent(const Justify& val);
	void setAlignItems(const Align& val);
	void setFlexDirection(const FlexDirection& flexDirection);
	void setFlexGrow(const float& val);
	void setFlexShrink(const float& val);
	void setWidth(const float& w);
	void setHeight(const float& h);
	void setMargin(const float& val);
	void setMargin(const float& left, const float& top, const float& right, const float& bottom);
	void setMargin(const Edge& type, const float& val);
	void setPadding(const float& val);
	void setPadding(const float& left, const float& top, const float& right, const float& bottom);
	void setPadding(const Edge& type, const float& val);
	void setSize(const float& w, const float& h);
	void setBorderWidth(const float& width);
	void setBorderColor(const Color& color); 
	void setBackgroundColor(const Color& color);
	void setRadius(float r);
	void setRadius(float lt, float rt, float rb, float lb);
	void setCaption(bool flag);
	bool getCaption();
	void paint(SkCanvas* canvas);
	Position getPosition();
	Size getSize();
	bool hittest(const int& x, const int& y);
	
public:
	friend class MouseEvent;
protected:
	void layout(const float& w,const float& h);
protected:
private:
	void paintRect(SkCanvas* canvas, const SkPaint& paint, const SkRect& rect);
	void calculateGlobalPos(const std::vector<Element*>& children);
private:
	Element* parent;
	std::vector<Element*> children;
	YGNode* node;
	float borderWidth;
	float radiusLT{ 0.f }, radiusRT{ 0.f }, radiusRB{ 0.f }, radiusLB{ 0.f };
	Color bgColor{ 0x00000000 },borderColor{ 0x00000000 };
	bool isCaption{ false };
	float globalX{ 0 }, globalY{ 0 };

};

