#include <Windows.h>
#include <App.h>
#include <WindowNormal.h>
#include <WindowFrameless.h>

int APIENTRY wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPTSTR lpCmdLine, _In_ int nCmdShow)
{
    App::init(hInstance);
    
    WindowFrameless win;
    win.setWindowSize(1000, 800);
    win.setWindowToScreenCenter();
    win.setBackgroundColor(0xFF234567);
    win.setBorderColor(0xFF997890);
    win.setBorderWidth(4.0f);


    win.setAlignItems(Align::Center);
    win.setJustifyContent(Justify::Center);
    auto ele = new Element();
    ele->setSize(500, 500);
    ele->setBackgroundColor(0xFF876543);
    ele->setBorderColor(0xFF654321);
    ele->setBorderWidth(4.0f);
    win.addChild(ele);



    win.createNativeWindow();
    win.show();

    return App::exec();
}