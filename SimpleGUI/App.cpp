#include <yoga/Yoga.h>
#include "App.h"

std::unique_ptr<App> app;
YGConfig* layoutConfig;

App::App(HINSTANCE hInstance):hInstance{hInstance}
{
    auto hr = CoInitializeEx(NULL, COINIT_APARTMENTTHREADED);
    if (FAILED(hr))
    {
        MessageBox(NULL, L"Failed to initialize COM library", L"Error", MB_OK | MB_ICONERROR);
    }
    layoutConfig = YGConfigNew();
    //YGConfigSetPointScaleFactor(layoutConfig, 1.5f); //todo
}

YGConfig* App::getLayoutConfig()
{
    return layoutConfig;
}

App::~App() {

}

void App::init(HINSTANCE hInstance)
{
    app = std::unique_ptr<App>(new App(hInstance));//std::make_unique<App>(hInstance);
}

App* App::get() {
    return app.get();
}

int App::exec() {
    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    CoUninitialize();
    return 0;
}
