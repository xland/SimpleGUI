#include <WindowNormal.h>

#include "EventDemo.h"

EventDemo::EventDemo()
{
    win = std::make_unique<WindowNormal>();
    win->setTitle(L"SkiaGUI 示例窗口");
    win->setWindowSize(1000, 800);
    win->setWindowToScreenCenter();
    win->setBackgroundColor(0xFF234567);
}

EventDemo::~EventDemo()
{
}

void EventDemo::start() {

    win->setAlignItems(Align::Center);
    win->setJustifyContent(Justify::Center);

    auto ele = new Element();
    ele->setSize(120, 40);
    ele->setBackgroundColor(0xFF876543);
    ele->onMouseEnter([ele](const MouseEvent& event) {
        ele->setBackgroundColor(0xFF000000);
        ele->update();
        });
    ele->onMouseLeave([ele](const MouseEvent& event) {
        ele->setBackgroundColor(0xFFFFFFFF);
        ele->update();
        });
    win->addChild(ele);

    win->createNativeWindow();
    win->show();
}
