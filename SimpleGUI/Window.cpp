#include "Window.h"
#include "cutils.h"

static JSClassDef windowClassDef{
    .class_name{"WINDOW"},
    .finalizer{Window::WindowFinalizer}
};
static JSClassID WindowClassId;

JSValue Window::Close(JSContext* ctx, JSValueConst this_val, int argc, JSValueConst* argv)
{
    Window* win = (Window*)JS_GetOpaque2(ctx, this_val, WindowClassId);
    return JS_NewInt32(ctx, 1);
}

void Window::Register(JSContext* ctx)
{
    

    JSValue proto;
	JS_NewClassID(&WindowClassId);
	int a = JS_NewClass(JS_GetRuntime(ctx), WindowClassId, &windowClassDef);
    proto = JS_NewObject(ctx);
    const JSCFunctionListEntry funcs[] = { 
        JSCFunctionListEntry {
            .name{"close"},
            .prop_flags{(1 << 1) | (1 << 0)},
            .u{
                .func {
                    .length{0},
                    .cproto{JS_CFUNC_generic},
                    .cfunc{
                        .generic = Window::Close
                    }
                }
            }
        }
    };
    JS_SetPropertyFunctionList(ctx, proto, funcs,countof(funcs));
    JS_SetClassProto(ctx, WindowClassId, proto);

    //JS_SetModuleExportList(ctx, m, js_os_funcs, countof(js_os_funcs));
}
void Window::WindowFinalizer(JSRuntime* rt, JSValue val)
{
    Window* win = (Window*)JS_GetOpaque(val, WindowClassId);
    if (win) {
        delete win;
    }
}
