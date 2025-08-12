#include "App.h"
#include "WindowNormal.h"
#include "Util.h"
#include "dwmapi.h"
#include "private\WindowBaseImpl.h"



void WindowNormal::createNativeWindow()
{
    auto pos = getPosition();
    auto size = getSize();
    winImpl = std::make_unique<WindowBaseImpl>(size.w, size.h);
    hwnd = CreateWindowEx(WS_EX_APPWINDOW, getWinClsName().data(), title.data(), WS_OVERLAPPEDWINDOW,
        pos.x, pos.y, size.w, size.h, nullptr, nullptr, App::get()->hInstance, nullptr);
    SetWindowLongPtr(hwnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(this));
    RECT clientRect;
    GetClientRect(hwnd, &clientRect);
    int w = clientRect.right;
    int h = clientRect.bottom;
    winImpl->resize(w, h);
    layout(w, h);
}

