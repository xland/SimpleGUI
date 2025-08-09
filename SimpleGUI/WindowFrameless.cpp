#include <dwmapi.h>
#include "WindowFrameless.h"

WindowFrameless::WindowFrameless()
{
}

WindowFrameless::~WindowFrameless()
{
}

void WindowFrameless::setFrameLess()
{
    MARGINS margins = { 1, 1, 1, 1 };
    DwmExtendFrameIntoClientArea(hwnd, &margins);
    int value = 2;
    DwmSetWindowAttribute(hwnd, DWMWA_NCRENDERING_POLICY, &value, sizeof(value));
    DwmSetWindowAttribute(hwnd, DWMWA_ALLOW_NCPAINT, &value, sizeof(value));
}
