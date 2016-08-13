#include <thread>
#include <windows.h>
#include <GL/gl.h>
#include <GL/glu.h>

#include "WWindow.hpp"
#include "Assert.hpp"
#include "Time.hpp"

// Static Variables
WWindow* WWindow::instancePointer;
bool WWindow::registeredWindowClass;
HINSTANCE WWindow::hInstance;
HINSTANCE WWindow::hPrevInstance;
LPSTR WWindow::lpCmdLine;
int WWindow::nCmdShow;

// Special stupid callback function that window bitches about
LRESULT CALLBACK windowCallbackFunction(HWND windowHandle, UINT windowMessage, WPARAM windowParameters, LPARAM lParameters){
    PAINTSTRUCT paintStruct;

    switch(windowMessage){
    case WM_PAINT:
    	WWindow::Instance()->Draw();
    	BeginPaint(windowHandle, &paintStruct);
    	EndPaint(windowHandle, &paintStruct);
        InvalidateRect(windowHandle, NULL, false);
    	return 0;
    case WM_CLOSE:
        DestroyWindow(windowHandle);
        WWindow::Instance()->game->End();
        return 0;
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    case WM_SIZE:
    	WWindow::Instance()->Resize(LOWORD(lParameters), HIWORD(lParameters));
        PostMessage(windowHandle, WM_PAINT, 0, 0);
    	return 0;
    }

    return DefWindowProc(windowHandle, windowMessage, windowParameters, lParameters);
}

WWindow* WWindow::Instance(){
    if(!instancePointer){
        instancePointer = new  WWindow(0, 0, 512, 512, "Phoenix Engine");
    }
    return instancePointer;
}

WWindow::WWindow(int x, int y, int width, int height, const char* title){
    int n;
    DWORD bufferingTypeFlags = PFD_DOUBLEBUFFER;
    BYTE  colorType  = PFD_TYPE_RGBA;
    int pixelFormat;
    LOGPALETTE* logPalette;
    PIXELFORMATDESCRIPTOR pixelFormatDescriptor;

    if(!WWindow::registeredWindowClass){
    	hInstance = GetModuleHandle(NULL);
    	windowClass.style         = CS_OWNDC;
    	windowClass.lpfnWndProc   = (WNDPROC)windowCallbackFunction;
    	windowClass.cbClsExtra    = 0;
    	windowClass.cbWndExtra    = 0;
    	windowClass.hInstance     = hInstance;
    	windowClass.hIcon         = LoadIcon(NULL, IDI_WINLOGO);
    	windowClass.hCursor       = LoadCursor(NULL, IDC_ARROW);
    	windowClass.hbrBackground = NULL;
    	windowClass.lpszMenuName  = NULL;
    	windowClass.lpszClassName = "OpenGL";

    	Assert_(RegisterClass(&windowClass), "Failed to register window class.");
    }

    windowHandle = CreateWindow("OpenGL", title, WS_OVERLAPPEDWINDOW | WS_CLIPSIBLINGS | WS_CLIPCHILDREN, x, y, width, height, NULL, NULL, hInstance, NULL);
    Assert_(windowHandle, "Error creating window handle.");
    hardwareDeviceContext = GetDC(windowHandle);

    // CLEAR THESE BITS
    memset(&pixelFormatDescriptor, 0, sizeof(pixelFormatDescriptor));
    pixelFormatDescriptor.nSize        = sizeof(pixelFormatDescriptor);
    pixelFormatDescriptor.nVersion     = 1;
    pixelFormatDescriptor.dwFlags      = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | bufferingTypeFlags;
    pixelFormatDescriptor.iPixelType   = colorType;
    pixelFormatDescriptor.cDepthBits   = 32;
    pixelFormatDescriptor.cColorBits   = 32;

    pixelFormat = ChoosePixelFormat(hardwareDeviceContext, &pixelFormatDescriptor);
    Assert_(pixelFormat, "Could not find a suitable pixel format.");
    bool couldSetPixelFormat = SetPixelFormat(hardwareDeviceContext, pixelFormat, &pixelFormatDescriptor);
    Assert_(couldSetPixelFormat, "Could not set pixel format specified");
    DescribePixelFormat(hardwareDeviceContext, pixelFormat, sizeof(PIXELFORMATDESCRIPTOR), &pixelFormatDescriptor);

    if(pixelFormatDescriptor.dwFlags & PFD_NEED_PALETTE || pixelFormatDescriptor.iPixelType == PFD_TYPE_COLORINDEX){

    	n = 1 << pixelFormatDescriptor.cColorBits;
    	if(n > 256){
            n = 256;
        }

    	logPalette = (LOGPALETTE*)malloc(sizeof(LOGPALETTE) + sizeof(PALETTEENTRY) * n);
    	memset(logPalette, 0, sizeof(LOGPALETTE) + sizeof(PALETTEENTRY) * n);
    	logPalette->palVersion = 0x300;
    	logPalette->palNumEntries = n;

    	GetSystemPaletteEntries(hardwareDeviceContext, 0, n, &logPalette->palPalEntry[0]);

    	/* if the pixel type is RGBA, then we want to make an RGB ramp,
    	   otherwise (color index) set individual colors. */
    	if (pixelFormatDescriptor.iPixelType == PFD_TYPE_RGBA) {
    	    int redMask = (1 << pixelFormatDescriptor.cRedBits) - 1;
    	    int greenMask = (1 << pixelFormatDescriptor.cGreenBits) - 1;
    	    int blueMask = (1 << pixelFormatDescriptor.cBlueBits) - 1;
    	    int i;

    	    /* fill in the entries with an RGB color ramp. */
    	    for (i = 0; i < n; ++i) {
    		logPalette->palPalEntry[i].peRed =
    		    (((i >> pixelFormatDescriptor.cRedShift)   & redMask)   * 255) / redMask;
    		logPalette->palPalEntry[i].peGreen =
    		    (((i >> pixelFormatDescriptor.cGreenShift) & greenMask) * 255) / greenMask;
    		logPalette->palPalEntry[i].peBlue =
    		    (((i >> pixelFormatDescriptor.cBlueShift)  & blueMask)  * 255) / blueMask;
    		logPalette->palPalEntry[i].peFlags = 0;
    	    }
    	} else {
    	    logPalette->palPalEntry[0].peRed = 0;
    	    logPalette->palPalEntry[0].peGreen = 0;
    	    logPalette->palPalEntry[0].peBlue = 0;
    	    logPalette->palPalEntry[0].peFlags = PC_NOCOLLAPSE;
    	    logPalette->palPalEntry[1].peRed = 255;
    	    logPalette->palPalEntry[1].peGreen = 0;
    	    logPalette->palPalEntry[1].peBlue = 0;
    	    logPalette->palPalEntry[1].peFlags = PC_NOCOLLAPSE;
    	    logPalette->palPalEntry[2].peRed = 0;
    	    logPalette->palPalEntry[2].peGreen = 255;
    	    logPalette->palPalEntry[2].peBlue = 0;
    	    logPalette->palPalEntry[2].peFlags = PC_NOCOLLAPSE;
    	    logPalette->palPalEntry[3].peRed = 0;
    	    logPalette->palPalEntry[3].peGreen = 0;
    	    logPalette->palPalEntry[3].peBlue = 255;
    	    logPalette->palPalEntry[3].peFlags = PC_NOCOLLAPSE;
    	}

    	hPalette = CreatePalette(logPalette);
    	if(hPalette){
    	    SelectPalette(hardwareDeviceContext, hPalette, FALSE);
    	    RealizePalette(hardwareDeviceContext);
    	}

    	free(logPalette);
    }

    ReleaseDC(windowHandle, hardwareDeviceContext);
}

void WWindow::Start(){
    if(windowHandle){
        hardwareGLRenderContext = wglCreateContext(hardwareDeviceContext);
        wglMakeCurrent(hardwareDeviceContext, hardwareGLRenderContext);

        glEnable(GL_DEPTH_TEST);

        ShowWindow(windowHandle, nCmdShow);

        while(GetMessage(&windowMessage, windowHandle, 0, 0) > 0){
            TranslateMessage(&windowMessage);
            DispatchMessage(&windowMessage);
        }
    }
}

void WWindow::Resize(int newWidth, int newHeight){
    glViewport(0, 0, newWidth, newHeight);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0, (float)newWidth/newHeight, 0.001, 100.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void WWindow::Draw(){
    game->Draw();
    SwapBuffers(hardwareDeviceContext);
    game->notifyHasDrawn();

}
