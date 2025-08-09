#include <Windows.h>
#include <App.h>
#include <WindowNormal.h>

int APIENTRY wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPTSTR lpCmdLine, _In_ int nCmdShow)
{
    App::init(hInstance);
    
    WindowNormal win;
    win.setSize(1000, 800);
    win.setPosition(100, 100);
    win.setAlignItems(Align::Center);
    win.setJustifyContent(Justify::Center);

    auto ele = new Element();
    ele->setSize(500, 500);

    win.addChild(ele);
    win.createNativeWindow();
    win.show();

    return App::exec();
}