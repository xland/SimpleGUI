#include <yoga/Yoga.h>

#include "Element.h"
#include "App.h"
#include "WindowBase.h"
#include "private\WindowBaseImpl.h"

WindowBase::WindowBase() :winPosition(0, 0), winSize(980, 680)
{

}
WindowBase::~WindowBase() {

}
void WindowBase::show() {
    ShowWindow(hwnd, SW_SHOW);     // 或者 SW_SHOWNORMAL / SW_SHOWDEFAULT
    UpdateWindow(hwnd);
}

void WindowBase::resetWindowToScreenCenter()
{
    int screenWidth = GetSystemMetrics(SM_CXSCREEN);
    int screenHeight = GetSystemMetrics(SM_CYSCREEN);
    auto size = getWindowSize();
    int x{ (screenWidth - size.w) / 2 };
    int y{ (screenHeight - size.h) / 2 };
    setWindowPosition(x,y);
    SetWindowPos(hwnd, NULL, x, y, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
}

void WindowBase::setWindowToScreenCenter()
{
    int screenWidth = GetSystemMetrics(SM_CXSCREEN);
    int screenHeight = GetSystemMetrics(SM_CYSCREEN);
    auto size = getWindowSize();
    int x{ (screenWidth - size.w) / 2 };
    int y{ (screenHeight - size.h) / 2 };
    setWindowPosition(x, y);
}

void WindowBase::setTitle(const std::wstring& title)
{
    this->title = title;
}

const std::wstring& WindowBase::getTitle()
{
    return title;
}

const Position& WindowBase::getWindowPosition()
{
    return winPosition;
}

const Size& WindowBase::getWindowSize()
{
    return winSize;
}

void WindowBase::resetWindowSize(const int& w, const int& h)
{
    winSize.w = w;
    winSize.h = h;
    SetWindowPos(hwnd, NULL, 0, 0, w, h, SWP_NOMOVE | SWP_NOZORDER);
}

void WindowBase::resetWindowPosition(const int& x, const int& y)
{
    winPosition.x = x;
    winPosition.y = y;
    SetWindowPos(hwnd, NULL, x, y, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
}
void WindowBase::setWindowSize(const int& w, const int& h)
{
    winSize.w = w;
    winSize.h = h;
}

void WindowBase::setWindowPosition(const int& x, const int& y)
{
    winPosition.x = x;
    winPosition.y = y;
}

LRESULT CALLBACK WindowBase::routeWindowMsg(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    auto winObj = reinterpret_cast<WindowBase*>(GetWindowLongPtr(hwnd, GWLP_USERDATA));
    if (winObj)
    {
        return winObj->windowMsgProc(hwnd, msg, wParam, lParam);
    }
    else {
        return DefWindowProc(hwnd, msg, wParam, lParam);
    }
}

LRESULT CALLBACK WindowBase::windowMsgProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) 
{
    switch (msg)
    {
    case WM_NCDESTROY:
    {
        SetWindowLongPtr(hwnd, GWLP_USERDATA, 0);
        PostQuitMessage(0);
        return 0;
    }
    case WM_DESTROY:
    {
        SetWindowLongPtr(hwnd, GWLP_USERDATA, 0);
        PostQuitMessage(0);
        return 0;
    }
    case WM_MOVE: 
    {
        setWindowPosition(LOWORD(lParam), HIWORD(lParam));        
        return 0;
    }
    case WM_SIZE:
    {
        int w{ LOWORD(lParam) }, h{ HIWORD(lParam) };
        setSize(w,h);
        winImpl->resize(w, h);
        layout(w, h);
        return 0;
    }
    //case WM_SETCURSOR: {
    //    return 1;
    //}
    //case WM_ERASEBKGND:
    //{
    //    return 1;
    //}
    case WM_PAINT: {
        //PAINTSTRUCT ps;
        //HDC hdc = BeginPaint(hwnd, &ps);
        //EndPaint(hwnd, &ps);
        winImpl->paintElement(this);
        paintArea();
        return 0;
    }
    case WM_LBUTTONDBLCLK:
    {
        return 0;
    }
    case WM_RBUTTONDOWN:
    {
        return 0;
    }
    case WM_MOUSEMOVE:
    {
        windowMouseMove(LOWORD(lParam), HIWORD(lParam));
        return 0;
    }
    case WM_LBUTTONDOWN:
    {
        return 0;
    }
    case WM_LBUTTONUP:
    {
        return 0;
    }
    case WM_KEYDOWN:
    {
        switch (wParam)
        {
        case VK_DELETE: {
            return 0;
        }
        case VK_LEFT: {
            return 0;
        }
        case VK_RIGHT: {
            return 0;
        }
        case VK_ESCAPE: {
            return 0;
        }
        case VK_SHIFT: {
            return 0;
        }
        case VK_CONTROL: {
            return 0;
        }
        }
        return 0;
    }
    case WM_KEYUP:
    {
        switch (wParam)
        {
        case VK_SHIFT: {
            return 0;
        }
        case VK_CONTROL: {
            return 0;
        }
        }
        return 0;
    }
    case WM_CHAR:
    {
        return 1;
    }
    case WM_IME_STARTCOMPOSITION:
    {
        break;
    }
    case WM_IME_ENDCOMPOSITION:
    {
        break;
    }
    case WM_IME_NOTIFY:
    {
        switch (wParam)
        {
        case IMN_SETOPENSTATUS:
            break;
        default:
            break;
        }
        break;
    }
    }
    return customMsgProc(hwnd, msg, wParam, lParam);
}

void WindowBase::windowMouseMove(const int& x, const int& y)
{
    MouseEvent e(x,y);
    auto ele = getElementByPosition(x, y);
    e.setRelativePosition(ele);
    ele->mouseMove(e);
    ele->mouseEnter(e);
}

void WindowBase::paintArea()
{
    PAINTSTRUCT ps;
    HDC hdc = BeginPaint(hwnd, &ps);
    auto size = getSize();
    auto pix = winImpl->getPix();
    BITMAPINFO bmi = { sizeof(BITMAPINFOHEADER), size.w, size.h, 1, 32, BI_RGB, size.h * 4 * size.w, 0, 0, 0, 0 };
    SetDIBitsToDevice(hdc, 0, 0, size.w, size.h, 0, 0, 0, size.h, pix.addr(), &bmi, DIB_RGB_COLORS);
    EndPaint(hwnd, &ps);
}

LRESULT CALLBACK WindowBase::customMsgProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    return DefWindowProc(hwnd, msg, wParam, lParam);
}

const std::wstring& WindowBase::getWinClsName()
{
    static std::wstring clsName = [] {
        WNDCLASSEXW wcex;
        wcex.cbSize = sizeof(WNDCLASSEX);
        wcex.style = CS_HREDRAW | CS_VREDRAW;
        wcex.lpfnWndProc = &WindowBase::routeWindowMsg;
        wcex.cbClsExtra = 0;
        wcex.cbWndExtra = 0;
        wcex.hInstance = App::get()->hInstance;
        wcex.hIcon = LoadIcon(wcex.hInstance, (LPCTSTR)IDI_WINLOGO);
        wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
        wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
        wcex.lpszMenuName = nullptr;
        wcex.lpszClassName = L"SimpleGUI";
        wcex.hIconSm = LoadIcon(wcex.hInstance, (LPCTSTR)IDI_WINLOGO);
        RegisterClassExW(&wcex);
        return wcex.lpszClassName;
        }();
    return clsName;
}

Element* WindowBase::getElementByPosition(int x, int y)
{
    Element* result = this;
    auto children = &result->getChildren();
    while (children->size() > 0) {
        bool flag{ false };
        for (auto& child : *children) //遍历子元素
        {
            if (child->hittest(x,y)) //命中测试
            {
                flag = true;
                result = child;
                children = &result->getChildren();
                break; //结束本层级的遍历，开始遍历下一个层级，找到最底层的元素
            }
        }
        if (!flag) {
            break;//上级命中，但本级没有命中，直接退出循环。
        }
    }
    return result;
}

HWND WindowBase::getHandle()
{
    return hwnd;
}
