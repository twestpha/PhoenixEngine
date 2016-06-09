#include <windows.h>

#pragma once

class WWindow {
public:
    WWindow();
    WWindow(int x, int y, int width, int height, const char* title);

    void Update();

    static void Draw(HDC hardwareDeviceContext);
private:
    static bool registeredWindowClass;
    WNDCLASSEX windowClass;
    HWND windowHandle;
    MSG windowMessage;
    HPALETTE hPalette;
};
