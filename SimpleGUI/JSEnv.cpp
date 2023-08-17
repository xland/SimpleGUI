#include "JSEnv.h"
#include "Window.h"

static JSEnv* env;
JSContext* ctx;
JSRuntime* rt;

JSEnv::JSEnv()
{
    rt = JS_NewRuntime();
    if (!rt) {
        int a = 1;
    }
    ctx = JS_NewContext(rt);
    if (!ctx) {
        //cannot allocate JS context
        int a = 1;
    }
    JS_SetModuleLoaderFunc(rt, NULL, js_module_loader, NULL);
#ifdef DEBUG
    js_std_init_handlers(rt);
    js_init_module_std(ctx, "std");
    js_std_add_helpers(ctx, 0, nullptr);
#endif // DEBUG
    js_init_module_os(ctx, "os");

    JSModuleDef* m;
    m = JS_NewCModule(ctx, "sg", &JSEnv::RegModel);
    if (!m)
    {
        //
        int a = 1;
    }
    auto ret = JS_AddModuleExport(ctx, m, "Window");
    LoadIndexJs(ctx);  
    
}

JSEnv::~JSEnv()
{
#ifdef DEBUG
    js_std_free_handlers(rt);
#endif // DEBUG    
    JS_FreeContext(ctx);
    JS_FreeRuntime(rt);
}

void JSEnv::Init()
{
    env = new JSEnv();
}

JSEnv* JSEnv::Get()
{
    return env;
}


JSContext* JSEnv::GetContext()
{
    return ctx;
}

int JSEnv::RegModel(JSContext* ctx, JSModuleDef* m)
{
    Window::Register(ctx,m);
    return 0;
}

void JSEnv::LoadIndexJs(JSContext* ctx)
{
    uint8_t* buf;
    size_t buf_len;
    buf = js_load_file(ctx, &buf_len, "index.js");
    if (!buf) {
        int a = 1;
        //load js error
    }
    JSValue val;
    char* buf1 = reinterpret_cast<char*>(const_cast<uint8_t*>(buf));
    val = JS_Eval(ctx, buf1, buf_len, "index.js", JS_EVAL_TYPE_MODULE);
    if (JS_IsException(val)) {
        js_std_dump_error(ctx);
        //error
    }
    JS_FreeValue(ctx, val);
    js_free(ctx, buf);
}