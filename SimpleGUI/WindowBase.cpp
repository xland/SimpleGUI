#include "App.h"
#include "WindowBase.h"
#include "private\WindowBaseImpl.h"

WindowBase::WindowBase() {

}
WindowBase::~WindowBase() {

}
void WindowBase::show() {
    ShowWindow(hwnd, SW_SHOW);     // 或者 SW_SHOWNORMAL / SW_SHOWDEFAULT
    UpdateWindow(hwnd);
}

void WindowBase::moveToScreenCenter()
{
    int screenWidth = GetSystemMetrics(SM_CXSCREEN);
    int screenHeight = GetSystemMetrics(SM_CYSCREEN);
    auto size = getSize();
    setSize((screenWidth - size.w) / 2, (screenHeight - size.h) / 2);
    //todo
}

void WindowBase::setTitle(const std::wstring& title)
{
    this->title = title;
}

const std::wstring& WindowBase::getTitle()
{
    return title;
}

LRESULT CALLBACK WindowBase::routeWindowMsg(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    auto winObj = reinterpret_cast<WindowBase*>(GetWindowLongPtr(hwnd, GWLP_USERDATA));
    if (winObj != nullptr)
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
    case WM_MOVE: 
    {
        setPosition(LOWORD(lParam), HIWORD(lParam));
        return 0;
    }
    case WM_SIZE:
    {
        int w{ LOWORD(lParam) }, h{ HIWORD(lParam) };
        setSize(w,h);
        winImpl->resize(w, h);
        return 0;
    }
    //case WM_SETCURSOR: {
    //    return 1;
    //}
    //case WM_ERASEBKGND:
    //{
    //    return 1;
    //}
    //case WM_PAINT:
    //{
    //    return 0;
    //}
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
    case WM_DESTROY:
    {
        PostQuitMessage(0);
        return 1;
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
