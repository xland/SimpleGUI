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