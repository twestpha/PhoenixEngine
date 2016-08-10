#include <windows.h>

#include "Game.hpp"

#ifndef WINDOWS_WINDOW_H
#define WINDOWS_WINDOW_H

class WWindow {
public:
    Game* game;

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

    unsigned long frameCount;
    double totalTime;
    double maxDrawTime;
};

#endif
