#pragma once
#include <Windows.h>
#include <stdio.h>
#include <string>
#include <stdlib.h>
#include "blend2d.h"
#include "quickjs.h"

#ifdef DEBUG
void InitDebuger();
#endif
std::string ConvertToUTF8(const std::wstring& wstr);
std::string ConvertToUTF8(const LPWSTR& wstr);
std::wstring ConvertToWideChar(const std::string& str);
constexpr JSCFunctionListEntry MakeJsFunc(const char* name, uint8_t length, JSCFunction* func) {
    return JSCFunctionListEntry{
        .name{name},
        .prop_flags{JS_PROP_WRITABLE | JS_PROP_CONFIGURABLE},
        .def_type{JS_DEF_CFUNC},
        .magic{0},
        .u = {.func = {0, JS_CFUNC_generic, {.generic = func}}}
    };
};

bool GetPropertyVal(JSContext* ctx, JSValueConst& obj, const char* name, int& out);
bool GetPropertyVal(JSContext* ctx, JSValueConst& obj, const char* name, bool& out);
bool GetPropertyVal(JSContext* ctx, JSValueConst& obj, const char* name, std::wstring& out);
bool GetPropertyVal(JSContext* ctx, JSValueConst& obj, BLBoxI& out);
