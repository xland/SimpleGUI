#include <Windows.h>
#include <App.h>
#include <WindowBase.h>
#include <WindowNormal.h>
#include <WindowFrameless.h>

void winLayoutCenter(WindowBase& win) {
    win.setAlignItems(Align::Center);
    win.setJustifyContent(Justify::Center);
    auto ele = new Element();
    ele->setSize(500, 500);
    ele->setBackgroundColor(0xFF876543);
    win.addChild(ele);
}

void winLeftRightLayout(WindowBase& win)
{
    win.setFlexDirection(FlexDirection::Row);
    auto left = new Element();
    left->setSize(300,SizeNaN);
    left->setBackgroundColor(0xFF876543);
    win.addChild(left);

    auto right = new Element();
    right->setFlexGrow(1.f);
    right->setFlexShrink(1.f);
    right->setBackgroundColor(0xFF9988aa);
    win.addChild(right);
}


int APIENTRY wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPTSTR lpCmdLine, _In_ int nCmdShow)
{
    App::init(hInstance);
    
    WindowFrameless win;
    win.setWindowSize(1000, 800);
    win.setWindowToScreenCenter();
    win.setBackgroundColor(0xFF234567);
    //winLayoutCenter(win);
    winLeftRightLayout(win);
    win.createNativeWindow();
    win.show();

    return App::exec();
}