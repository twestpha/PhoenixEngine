#include <windows.h>

#pragma once

class WWindow {
public:
    static WWindow* Instance();
    static WWindow* instancePointer;

    void Start();

    void Draw();
private:
    WWindow(int x, int y, int width, int height, const char* title);

    static bool registeredWindowClass;

    WNDCLASS windowClass;
    HDC hardwareDeviceContext;
    HWND windowHandle;
    HGLRC hardwareGLRenderContext;
    MSG windowMessage;
    HPALETTE hPalette;
};
