#pragma once
#include "Element.h"
class ElementBox:public Element
{
public:
	virtual void paint(SkCanvas* canvas) override;
	std::vector<Element*>* getChildren() override;
	void insertChild(const int& index, Element* ele);
	void addChild(Element* ele);
	/// <summary>
	/// 用来设置 子元素在交叉轴 上的对齐方式。
	/// 主轴 ：由 flex-direction 决定（水平方向或垂直方向）。
	/// 交叉轴 ：与主轴垂直的方向。
	/// </summary>
	/// <param name="val"></param>
	void setAlignItems(const Align& val);
	/// <summary>
	/// 控制子元素在 主轴的分布方式
	/// </summary>
	/// <param name="val"></param>
	void setJustifyContent(const Justify& val);
	/// <summary>
	/// 设置主轴的方向
	/// </summary>
	/// <param name="flexDirection"></param>
	void setFlexDirection(const FlexDirection& flexDirection);
	void layout(const float& w, const float& h, WindowBase* win = nullptr);
protected:
	void casecadeShown();
private:
	void calculateGlobalPos(std::vector<Element*>* children, WindowBase* win = nullptr);
private:
	std::vector<Element*> children;
};

