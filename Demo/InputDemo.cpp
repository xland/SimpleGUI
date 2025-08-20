#include <WindowNormal.h>
#include <TextArea.h>
#include "InputDemo.h"



InputDemo::InputDemo()
{
    win = std::make_unique<WindowNormal>();
    win->setTitle(L"SkiaGUI 示例窗口");
    win->setWindowSize(1000, 800);
    win->setWindowToScreenCenter();
    win->setBackgroundColor(0xFFFFFFFF);
}

InputDemo::~InputDemo()
{
}

void InputDemo::start() {

    win->setAlignItems(Align::Center);
    win->setJustifyContent(Justify::Center);

    auto ele = new TextArea();
    ele->setSizePercent(100, 100);
    ele->setBackgroundColor(0xFFFFFFFF);
    win->addChild(ele);

    win->createNativeWindow();
    win->show();
}

