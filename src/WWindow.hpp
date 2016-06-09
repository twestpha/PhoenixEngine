#include <windows.h>

#pragma once

const char g_szClassName[] = "defaultWindowClass";

class WWindow {
public:
    WWindow(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow);
private:
    WNDCLASSEX windowClass;
    HWND windowHandle;
    MSG windowMessage;
};
