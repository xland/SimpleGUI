#include <WindowFrameless.h>
#include <WindowNormal.h>

#include "LayoutDemo.h"

LayoutDemo::LayoutDemo() 
{
    win = std::make_unique<WindowFrameless>();
    win->setWindowSize(1000, 800);
    win->setWindowToScreenCenter();
    win->setBackgroundColor(0xFF234567);
}
LayoutDemo::~LayoutDemo() 
{

}

void LayoutDemo::leftRight()
{
    win->setFlexDirection(FlexDirection::Row);
    auto left = new Element();
    left->setSize(300, SizeNaN);
    left->setBackgroundColor(0xFF876543);
    win->addChild(left);

    auto right = new Element();
    right->setFlexGrow(1.f);
    right->setFlexShrink(1.f);
    right->setBackgroundColor(0xFF9988aa);
    win->addChild(right);

    win->createNativeWindow();
    win->show();
}

void LayoutDemo::topCenterBottom()
{
    win->setFlexDirection(FlexDirection::Column);

    auto top = new Element();
    top->setSize(SizeNaN, 80);
    top->setBackgroundColor(0xFF876543);
    win->addChild(top);

    auto center = new Element();
    center->setFlexGrow(1.f);
    center->setFlexShrink(1.f);
    center->setBackgroundColor(0xFF9988aa);
    win->addChild(center);

    auto bottom = new Element();
    bottom->setSize(SizeNaN, 40);
    bottom->setBackgroundColor(0xFF313951);
    win->addChild(bottom);

    win->createNativeWindow();
    win->show();
}



void LayoutDemo::verticalHorizontalCenter()
{
    win->setAlignItems(Align::Center);
    win->setJustifyContent(Justify::Center);
    auto ele = new Element();
    ele->setSize(500, 500);
    ele->setBackgroundColor(0xFF876543);
    win->addChild(ele);

    win->createNativeWindow();
    win->show();
}
