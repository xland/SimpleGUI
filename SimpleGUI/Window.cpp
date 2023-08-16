#include "Window.h"
#include "cutils.h"
#include "Util.h"
#include <windowsx.h>
#include "dwmapi.h"

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
    //todo js_free_rt已经帮我释放了资源，所以不能再delete，如果有其他指针，得自己调方法释放
    js_free_rt(rt, win);
}

JSValue Window::Close(JSContext* ctx, JSValueConst this_val, int argc, JSValueConst* argv)
{
    //todo 要想拿到Window对象指针，就用下面这一句
    //Window* win = (Window*)JS_GetOpaque(this_val, WindowClassId);
    return JS_NewInt32(ctx,222);
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
    auto s = new Window();
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

Window::Window()
{
    createWindow();
    ShowWindow(hwnd, SW_SHOW);
    UpdateWindow(hwnd);
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
    wcx.lpszClassName = L"ScreenCapture";
    if (!RegisterClassEx(&wcx))
    {
        MessageBox(NULL, L"注册窗口类失败", L"系统提示", NULL);
        return;
    }
    hwnd = CreateWindowEx(0, wcx.lpszClassName, wcx.lpszClassName, WS_OVERLAPPEDWINDOW, x, y, w, h, NULL, NULL, hinstance, static_cast<LPVOID>(this));
    BOOL attrib = TRUE;
    DwmSetWindowAttribute(hwnd, DWMWA_TRANSITIONS_FORCEDISABLED, &attrib, sizeof(attrib));
}

LRESULT CALLBACK Window::WindowProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch (msg)
    {
        case WM_NCCALCSIZE:
        {
            return 0;
        }
        case WM_SETCURSOR: {
            return 1;
        }
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

