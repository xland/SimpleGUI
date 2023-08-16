#include "Window.h"
#include "cutils.h"


static JSClassID WindowClassId;
void WindowFinalizer(JSRuntime* rt, JSValue val)
{
    Window* win = (Window*)JS_GetOpaque(val, WindowClassId);
    js_free_rt(rt, win);
}


static JSClassDef windowClassDef{
    .class_name{"Window"},
    .finalizer{&WindowFinalizer}
};

typedef struct {
    size_t width;
    size_t height;
} WindowStruct;

static JSValue Close(JSContext* ctx, JSValueConst this_val, int argc, JSValueConst* argv)
{
    return JS_NewInt32(ctx,222);
}

static JSValue AddEventListener(JSContext* ctx, JSValueConst this_val, int argc, JSValueConst* argv)
{
    return JS_NewInt32(ctx, 222);
}

static const JSCFunctionListEntry funcs[]{
    {
        .name{"close"}, 
        .prop_flags{JS_PROP_WRITABLE | JS_PROP_CONFIGURABLE}, 
        .def_type{JS_DEF_CFUNC}, 
        .magic{0}, 
        .u = {.func = {0, JS_CFUNC_generic, {.generic = &Close}}}
    }
};

static JSValue WindowNew(JSContext* ctx, JSValueConst jsThis, int argc, JSValueConst* argv)
{
    JSValue obj = JS_NewObjectClass(ctx, WindowClassId);
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
    JS_NewClassID(&WindowClassId);  //
    JS_NewClass(JS_GetRuntime(ctx), WindowClassId, &windowClassDef);
    proto = JS_NewObject(ctx);
    //JSCFunctionListEntry funcs[]{
    //    JSCFunctionListEntry{
    //        .name{"close"},
    //        .prop_flags{JS_PROP_WRITABLE | JS_PROP_CONFIGURABLE},
    //        .def_type{JS_DEF_CFUNC},
    //        .magic{0},
    //        .u{
    //            .func = {
    //                .length{1},
    //                .cproto{JS_CFUNC_generic},
    //                .cfunc{
    //                    .generic = &Close
    //                }
    //            }
    //        }
    //    }
    //};
    // 
    
    
    JS_SetPropertyFunctionList(ctx, proto, funcs, countof(funcs));
    JS_SetPropertyStr(ctx, proto, "allen", JS_NewInt32(ctx, 111));
    //JSValue val = JS_NewCFunction2(ctx, Close, "close", 1, JS_CFUNC_generic, 0);
    //JS_SetPropertyValue(ctx,proto,)

    obj = JS_NewCFunction2(ctx, &WindowNew, "Window", 1,JS_CFUNC_constructor, 0);
    JS_SetConstructor(ctx, obj, proto);
    JS_SetClassProto(ctx, WindowClassId, proto);
    JS_SetModuleExport(ctx, m, "Window", obj);
    






    //JS_CFUNC_DEF("exit", 1, js_std_exit);
    //JS_SetModuleExport(ctx, m, "close", js_new_std_file(ctx, stdin, FALSE, FALSE));
    //auto ret = JS_SetModuleExportList(ctx, m, funcs, count);

    
    //JSValue val;
    //val = JS_NewObject(ctx);
    //JS_SetPropertyFunctionList(ctx, val, e->u.prop_list.tab, e->u.prop_list.len);



    //JSValue val = JS_NewCFunction2(ctx, Close,"close", 1, JS_CFUNC_generic, 0);
    //auto ret = JS_SetModuleExport(ctx, m, "close", val);
    
}

