#include "Window.h"
#include "cutils.h"
#include "Util.h"
#include <windowsx.h>
#include "dwmapi.h"
#include "JSEnv.h"

JSClassID Window::WindowClassId{0};
std::string Window::className{"Window"};

//todo .func得第一个值0是啥意思，.magic是啥意思
static const JSCFunctionListEntry funcs[]{
    MakeJsFunc("close",0,&Window::Close),
    MakeJsFunc("addEventListener",0,&Window::AddEventListener),
};



void Window::WindowFinalizer(JSRuntime* rt, JSValue val)
{
    Window* win = (Window*)JS_GetOpaque(val, Window::WindowClassId);
    //todo js_free_rt已经帮我释放了资源，所以不能再delete win了
    //如果win持有其它指针，得在这里写delete释放
    js_free_rt(rt, win);
}

JSValue Window::Close(JSContext* ctx, JSValueConst this_val, int argc, JSValueConst* argv)
{
    Window* win = (Window*)JS_GetOpaque(this_val, WindowClassId);
    win->Close();
    return JS_NewInt32(ctx,222);
}
void Window::Close()
{

}

JSValue Window::Show(JSContext* ctx, JSValueConst this_val, int argc, JSValueConst* argv)
{
    Window* win = (Window*)JS_GetOpaque(this_val, WindowClassId);
    win->Show();
    return JS_NewInt32(ctx, 222);
}
void Window::Show()
{
    ShowWindow(hwnd, SW_SHOW);
    UpdateWindow(hwnd);
}

JSValue Window::AddEventListener(JSContext* ctx, JSValueConst this_val, int argc, JSValueConst* argv)
{
    JSValueConst func = argv[1];
    if (JS_IsNull(func)) {
        return JS_UNDEFINED;
    }
    if (!JS_IsFunction(ctx, func)) {
        return JS_UNDEFINED;
    }
    auto val = JS_NewInt32(ctx, 666);
    JSValue jsResult = JS_Call(ctx, func, this_val, 1, &val);
    JS_FreeValue(ctx, jsResult);
    JS_FreeValue(ctx, val);
    return JS_UNDEFINED;
}

JSValue Window::WindowNew(JSContext* ctx, JSValueConst jsThis, int argc, JSValueConst* argv)
{
    JSValue obj = JS_NewObjectClass(ctx, Window::WindowClassId);
    if (JS_IsException(obj))
    {
        return obj;
    }
    JSValueConst config = argv[0];
    int x{ 100 }, y{ 100 }, width{ 800 }, height{600};
    GetPropertyVal(ctx,config,"x", x);
    GetPropertyVal(ctx, argv[0], "y", y);
    GetPropertyVal(ctx, argv[0], "width", width);
    GetPropertyVal(ctx, argv[0], "height", height);
    bool frame{ true }, shadow{ true }, visible{ true }, center{true};
    GetPropertyVal(ctx, argv[0], "frame",frame);
    GetPropertyVal(ctx, argv[0], "shadow", shadow);
    GetPropertyVal(ctx, argv[0], "visible", visible);
    GetPropertyVal(ctx, argv[0], "center", center);
    std::wstring title{L"SimpleGUI"};
    GetPropertyVal(ctx, argv[0], "title", title);
    std::vector<BLBoxI> captionArea;
    JSValue captionAreaVal = JS_GetPropertyStr(ctx, argv[0], "captionArea");
    int64_t length{ 0 };
    JSValue jsLen = JS_GetPropertyLength(ctx, &length, captionAreaVal);
    for (size_t i = 0; i < length; i++)
    {
        JSValue item = JS_GetPropertyUint32(ctx, captionAreaVal, i);
        BLBoxI box;
        GetPropertyVal(ctx,item, box);
        captionArea.push_back(std::move(box));
        JS_FreeValue(ctx, item);
    }
    JS_FreeValue(ctx, captionAreaVal);
    auto s = new Window(x,y,width,height,frame,shadow,visible,center,title, captionArea);
    JS_SetOpaque(obj, s);
    return obj;
}

void Window::Register(JSContext* ctx, JSModuleDef* m)
{
    JSValue proto, obj;
    JS_NewClassID(&Window::WindowClassId);  //
    JSClassDef windowClassDef{
        .class_name{Window::className.c_str()},
        .finalizer{&Window::WindowFinalizer}
    };
    JS_NewClass(JS_GetRuntime(ctx), Window::WindowClassId, &windowClassDef);
    proto = JS_NewObject(ctx);    
    JS_SetPropertyFunctionList(ctx, proto, funcs, countof(funcs));
    //todo 加个字符串字段
    //JS_SetPropertyStr(ctx, proto, "allen", JS_NewInt32(ctx, 111));
    
    //JSValue val = JS_NewCFunction2(ctx, Close, "close", 1, JS_CFUNC_generic, 0);
    //JS_SetPropertyValue(ctx,proto,)

    obj = JS_NewCFunction2(ctx, &Window::WindowNew, Window::className.c_str(), 1, JS_CFUNC_constructor, 0);
    JS_SetConstructor(ctx, obj, proto);
    JS_SetClassProto(ctx, Window::WindowClassId, proto);
    JS_SetModuleExport(ctx, m, Window::className.c_str(), obj);

    //JS_CFUNC_DEF("exit", 1, js_std_exit);
    //JS_SetModuleExport(ctx, m, "close", js_new_std_file(ctx, stdin, FALSE, FALSE));
    //auto ret = JS_SetModuleExportList(ctx, m, funcs, count);

    
    //JSValue val;
    //val = JS_NewObject(ctx);
    //JS_SetPropertyFunctionList(ctx, val, e->u.prop_list.tab, e->u.prop_list.len);



    //JSValue val = JS_NewCFunction2(ctx, Close,"close", 1, JS_CFUNC_generic, 0);
    //auto ret = JS_SetModuleExport(ctx, m, "close", val);
    
}

Window::Window(int x, int y, int width, int height, bool frame, bool shadow, bool visible,bool center,std::wstring title, std::vector<BLBoxI> captionArea):
    x{x},y{y},width{width},height{height},
    frame{ frame }, shadow{ shadow }, visible{ visible }, center{center},
    title{title},
    captionArea{captionArea}
{
    createWindow();
    if (visible) {
        Show();
    }    
}

LRESULT CALLBACK Window::RouteWindowMessage(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    if (msg == WM_NCCREATE)
    {
        CREATESTRUCT* pCS = reinterpret_cast<CREATESTRUCT*>(lParam);
        LPVOID pThis = pCS->lpCreateParams;
        SetWindowLongPtr(hWnd, 0, reinterpret_cast<LONG_PTR>(pThis));
    }
    auto obj = reinterpret_cast<Window*>(GetWindowLongPtrW(hWnd, 0));
    return obj->WindowProc(hWnd, msg, wParam, lParam);
}

void Window::createWindow()
{
    auto hinstance = GetModuleHandle(NULL);
    WNDCLASSEX wcx{};
    wcx.cbSize = sizeof(wcx);
    wcx.style = CS_HREDRAW | CS_VREDRAW;
    wcx.lpfnWndProc = &Window::RouteWindowMessage;
    wcx.cbWndExtra = sizeof(Window*);
    wcx.hInstance = hinstance;
    wcx.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wcx.hCursor = LoadCursor(NULL, IDC_ARROW);
    wcx.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcx.lpszClassName = L"SimpleGUI";
    if (!RegisterClassEx(&wcx))
    {
        MessageBox(NULL, L"注册窗口类失败", L"系统提示", NULL);
        return;
    }
    if (center) {
        RECT rect;
        SystemParametersInfo(SPI_GETWORKAREA, 0, &rect, 0);
        x = (rect.right - width) / 2;
        y = (rect.bottom - height) / 2;
    }
    auto borderlessStyle = WS_POPUP | WS_THICKFRAME | WS_CAPTION | WS_SYSMENU | WS_MAXIMIZEBOX | WS_MINIMIZEBOX;
    this->hwnd = CreateWindowEx(WS_EX_APPWINDOW | WS_EX_WINDOWEDGE, 
        wcx.lpszClassName, title.c_str(), WS_OVERLAPPEDWINDOW, x, y, width, height, NULL, NULL, hinstance, static_cast<LPVOID>(this));
    if (!frame) {
        //BOOL attrib = TRUE;
        //DwmSetWindowAttribute(hwnd, DWMWA_TRANSITIONS_FORCEDISABLED, &attrib, sizeof(attrib));
        if (shadow) {
            auto borderlessStyle = WS_POPUP | WS_THICKFRAME | WS_SYSMENU;; //todo
            SetWindowLongPtr(hwnd, GWL_STYLE, borderlessStyle);
            static const MARGINS shadow_state{ 0, 0, 0, 1 };
            DwmExtendFrameIntoClientArea(hwnd, &shadow_state);
        }        
        SetWindowPos(hwnd, nullptr, 0, 0, 0, 0, SWP_NOZORDER | SWP_NOOWNERZORDER | SWP_NOMOVE | SWP_NOSIZE | SWP_FRAMECHANGED);
    }
    
}

LRESULT Window::hitTest(int x,int y) {
    if (!hwnd) return HTNOWHERE;
    RECT winRect;
    GetWindowRect(hwnd, &winRect);
    if (x > winRect.left && y > winRect.top && x < winRect.right && y < winRect.bottom) {
        if (resizable) {
            int borderWidth = 4;
            if (x < winRect.left + borderWidth && y < winRect.top + borderWidth) return HTTOPLEFT;
            else if (x < winRect.left + borderWidth &&  y > winRect.bottom - borderWidth) return HTBOTTOMLEFT;
            else if (x > winRect.right - borderWidth && y > winRect.bottom - borderWidth) return HTBOTTOMRIGHT;
            else if (x > winRect.right - borderWidth && y < winRect.top + borderWidth) return HTTOPRIGHT;
            else if (x < winRect.left + borderWidth) return HTLEFT;
            else if (x > winRect.right - borderWidth) return HTRIGHT;
            else if (y < winRect.top + borderWidth) return HTTOP;
            else if (y > winRect.bottom - borderWidth) return HTBOTTOM;
        }
        for (auto& box : this->captionArea)
        {
            if (box.contains(x - winRect.left, y - winRect.top)) {
                return HTCAPTION;
            }
        }
        return HTCLIENT;
    }
    else
    {
        return HTNOWHERE;
    }
}


LRESULT CALLBACK Window::WindowProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch (msg)
    {
        case WM_NCCALCSIZE:
        {
            
            if (!frame) {
                //这样可以将客户端区域扩展到包括框架在内的窗口大小,但不包括阴影部分
                return 0;
            }
            break;
        }
        case WM_NCHITTEST:
        {
            this->hwnd = hWnd;
            int x = GET_X_LPARAM(lParam);
            int y = GET_Y_LPARAM(lParam);
            return this->hitTest(x,y);
            break;
        }
        case WM_SIZE:
        {
            return 0;
        }
        //case WM_SETCURSOR: {
        //    return 1;
        //}
        case WM_TIMER: {
            return 1;
        }
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
    return DefWindowProc(hWnd, msg, wParam, lParam);
}

