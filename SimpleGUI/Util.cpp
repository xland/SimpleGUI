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
std::string ConvertToUTF8(const std::wstring& wstr)
{
    const int count = WideCharToMultiByte(CP_UTF8, 0, wstr.c_str(), (int)wstr.length(), NULL, 0, NULL, NULL);
    std::string str(count, 0);
    WideCharToMultiByte(CP_UTF8, 0, wstr.c_str(), -1, &str[0], count, NULL, NULL);
    return str;
}

std::string ConvertToUTF8(const LPWSTR& wstr)
{
    const int count = WideCharToMultiByte(CP_UTF8, 0, wstr, (int)wcslen(wstr), NULL, 0, NULL, NULL);
    std::string str(count, 0);
    WideCharToMultiByte(CP_UTF8, 0, wstr, -1, &str[0], count, NULL, NULL);
    return str;
}

std::wstring ConvertToWideChar(const std::string& str)
{
    int count = MultiByteToWideChar(CP_UTF8, 0, str.c_str(), -1, 0, 0);
    std::wstring wstr(count, 0);
    MultiByteToWideChar(CP_UTF8, 0, str.c_str(), -1, &wstr[0], count);
    return wstr;
}

bool GetPropertyVal(JSContext* ctx, JSValueConst& obj, const char* name,int& out)
{
    JSValue val = JS_GetPropertyStr(ctx, obj, name);
    if (JS_IsException(val)) {
        JS_FreeValue(ctx, val);
        return false;
    }
    if (JS_IsUndefined(val)) {
        JS_FreeValue(ctx, val);
        return false;
    }
    JS_ToInt32(ctx, &out, val);
    JS_FreeValue(ctx, val);
    return true;
}
bool GetPropertyVal(JSContext* ctx, JSValueConst& obj, const char* name, bool& out)
{
    JSValue val = JS_GetPropertyStr(ctx, obj, name);
    if (JS_IsException(val)) {
        JS_FreeValue(ctx, val);
        return false;
    }
    if (JS_IsUndefined(val)) {
        JS_FreeValue(ctx, val);
        return false;
    }
    out = (bool)JS_ToBool(ctx, val);
    JS_FreeValue(ctx, val);
    return true;
}

bool GetPropertyVal(JSContext* ctx, JSValueConst& obj, const char* name, std::wstring& out)
{
    JSValue val = JS_GetPropertyStr(ctx, obj, name);
    if (JS_IsException(val)) {
        JS_FreeValue(ctx, val);
        return false;
    }
    if (JS_IsUndefined(val)) {
        JS_FreeValue(ctx, val);
        return false;
    }
    std::string str{JS_ToCString(ctx, val)};
    out = ConvertToWideChar(str);
    JS_FreeValue(ctx, val);
    return true;
}

bool GetPropertyVal(JSContext* ctx, JSValueConst& obj, BLBoxI& out)
{
    GetPropertyVal(ctx,obj, "x0", out.x0);
    GetPropertyVal(ctx, obj, "y0", out.y0);
    GetPropertyVal(ctx, obj, "x1", out.x1);
    GetPropertyVal(ctx, obj, "y1", out.y1);
    return true;
}