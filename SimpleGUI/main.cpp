//#include <Windows.h>
//#include "Util.h"
//#include "JSEnv.h"


//int APIENTRY wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPTSTR lpCmdLine, _In_ int nCmdShow)
//{
//#ifdef DEBUG
//    InitDebuger();
//#endif
//    JSEnv::Init();
//    MSG msg;
//    while (GetMessage(&msg, NULL, 0, 0))
//    {
//        TranslateMessage(&msg);
//        DispatchMessage(&msg);
//    }
//    return 0;
//}



#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <windowsx.h>
#include <dwmapi.h>
#include <unknwn.h>
#include <gdiplus.h>
#pragma comment( lib, "dwmapi" )
#pragma comment( lib, "gdiplus" )
namespace gdip = Gdiplus;

INT_PTR CALLBACK MyDialogProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPWSTR    lpCmdLine,
    _In_ int       nCmdShow)
{
    // Initialize GDI+
    gdip::GdiplusStartupInput gdiplusStartupInput;
    ULONG_PTR gdipToken = 0;
    gdip::GdiplusStartup(&gdipToken, &gdiplusStartupInput, nullptr);

    struct MyDialog : DLGTEMPLATE {
        WORD dummy[3] = { 0 };  // unused menu, class and title
    }
    dlg;
    dlg.style = WS_POPUP | WS_CAPTION | DS_CENTER;
    dlg.dwExtendedStyle = 0;
    dlg.cdit = 0;  // no controls in template
    dlg.x = 0;
    dlg.y = 0;
    dlg.cx = 300;  // width in dialog units
    dlg.cy = 200;  // height in dialog units

    DialogBoxIndirectW(hInstance, &dlg, nullptr, MyDialogProc);

    gdip::GdiplusShutdown(gdipToken);

    return 0;
}


LRESULT hitTest(int x, int y,HWND hwnd) {
    RECT winRect;
    GetWindowRect(hwnd, &winRect);
    if (x > winRect.left && y > winRect.top && x < winRect.right && y < winRect.bottom) {
        if (true) {
            static int borderWidth = 6;
            if (x < winRect.left + borderWidth && y < winRect.top + borderWidth) {
                SetWindowLong(hwnd, DWLP_MSGRESULT, HTTOPLEFT);
            }
            else if (x < winRect.left + borderWidth && y > winRect.bottom - borderWidth) {
                SetWindowLong(hwnd, DWLP_MSGRESULT, HTBOTTOMLEFT);
            }
            else if (x > winRect.right - borderWidth && y > winRect.bottom - borderWidth) {
                SetWindowLong(hwnd, DWLP_MSGRESULT, HTBOTTOMRIGHT);
            }
            else if (x > winRect.right - borderWidth && y < winRect.top + borderWidth) {
                SetWindowLong(hwnd, DWLP_MSGRESULT, HTTOPRIGHT);
            }
            else if (x < winRect.left + borderWidth) {
                SetWindowLong(hwnd, DWLP_MSGRESULT, HTLEFT);
            }
            else if (x > winRect.right - borderWidth) {
                SetWindowLong(hwnd, DWLP_MSGRESULT, HTRIGHT);
            }
            else if (y < winRect.top + borderWidth) {
                SetWindowLong(hwnd, DWLP_MSGRESULT, HTTOP);
            }
            else if (y > winRect.bottom - borderWidth) {
                SetWindowLong(hwnd, DWLP_MSGRESULT, HTBOTTOM);
            }
            else if (x > winRect.left && y > winRect.top && x < winRect.left + 100 && y < winRect.top + 100) {
                SetWindowLong(hwnd, DWLP_MSGRESULT, HTCAPTION);
            }
        }
        //for (auto& box : this->captionArea)
        //{
        //    if (box.contains(x - winRect.left, y - winRect.top)) {
        //        return HTCAPTION;
        //    }
        //}
        return HTCLIENT;
    }
    else
    {
        return HTNOWHERE;
    }
}

INT_PTR CALLBACK MyDialogProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_INITDIALOG:
    {
        SetWindowTextW(hDlg, L"Borderless Window with Shadow");

        // This plays together with WM_NCALCSIZE.
        MARGINS m{ 0, 0, 0, 1 };
        DwmExtendFrameIntoClientArea(hDlg, &m);

        // Force the system to recalculate NC area (making it send WM_NCCALCSIZE).
        SetWindowPos(hDlg, nullptr, 0, 0, 0, 0,
            SWP_NOZORDER | SWP_NOOWNERZORDER | SWP_NOMOVE | SWP_NOSIZE | SWP_FRAMECHANGED);
        return TRUE;
    }
    case WM_NCCALCSIZE:
    {
        // Setting 0 as the message result when wParam is TRUE removes the
        // standard frame, but keeps the window shadow.
        if (wParam == TRUE)
        {
            SetWindowLong(hDlg, DWLP_MSGRESULT, 0);
            return TRUE;
        }
        return FALSE;
    }
    case WM_PAINT:
    {
        PAINTSTRUCT ps{ 0 };
        HDC hdc = BeginPaint(hDlg, &ps);
        // Draw with GDI+ to make sure the alpha channel is opaque.
        gdip::Graphics gfx{ hdc };
        gdip::SolidBrush brush{ gdip::Color{ 255, 255, 255 } };
        gfx.FillRectangle(&brush,
            static_cast<INT>(ps.rcPaint.left), static_cast<INT>(ps.rcPaint.top),
            static_cast<INT>(ps.rcPaint.right - ps.rcPaint.left), static_cast<INT>(ps.rcPaint.bottom - ps.rcPaint.top));
        EndPaint(hDlg, &ps);
        return TRUE;
    }
    case WM_NCHITTEST:
    {
        // Setting HTCAPTION as the message result allows the user to move 
        // the window around by clicking anywhere within the window.
        // Depending on the mouse coordinates passed in LPARAM, you may 
        // set other values to enable resizing.
        //SetWindowLong(hDlg, DWLP_MSGRESULT, HTCAPTION);
        int x = GET_X_LPARAM(lParam);
        int y = GET_Y_LPARAM(lParam);
        hitTest(x, y, hDlg);
        return TRUE;
    }
    case WM_COMMAND:
    {
        WORD id = LOWORD(wParam);
        if (id == IDOK || id == IDCANCEL)
        {
            EndDialog(hDlg, id);
            return TRUE;
        }
        return FALSE;
    }
    }
    return FALSE; // return FALSE to let DefDialogProc handle the message
}