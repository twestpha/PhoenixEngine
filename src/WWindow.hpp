#include <windows.h>

#pragma once

class WWindow {
public:
    static HINSTANCE hInstance;
    static HINSTANCE hPrevInstance;
    static LPSTR lpCmdLine;
    static int nCmdShow;

    static WWindow* Instance();
    static WWindow* instancePointer;

    void Start();
    void Resize(int newWidth, int newHeight);

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

    unsigned int frameCount;
    double totalTime;
};
