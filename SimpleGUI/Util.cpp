#include "Util.h"
#include <Windows.h>

#ifdef DEBUG
void InitDebuger() {
    AllocConsole();
    FILE* stream;
    freopen_s(&stream, "CON", "r", stdin);
    freopen_s(&stream, "CON", "w", stdout);
    freopen_s(&stream, "CON", "w", stderr);
}
#endif
bool GetPropertyVal(JSContext* ctx, JSValueConst& obj, const char* name,int* out)
{
    JSValue val = JS_GetPropertyStr(ctx, obj, name);
    if (JS_IsException(val)) {
        return false;
    }
    if (JS_IsUndefined(val)) {
        return false;
    }
    JS_ToInt32(ctx, out, val);
    return true;
}