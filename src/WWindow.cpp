#include <windows.h>
#include <GL/gl.h>
#include <GL/glu.h>

#include "WWindow.hpp"
#include "Assert.hpp"

VOID OnPaint(HDC hdc);

extern HDC hardwareDeviceContext;

HPALETTE hPalette = 0;

LRESULT CALLBACK windowCallbackFunction(HWND windowHandle, UINT windowMessage, WPARAM windowParameters, LPARAM lParameters){
    HDC hardwareDeviceContext;
    PAINTSTRUCT paintStruct;

    switch(windowMessage){
    case WM_CLOSE:
        DestroyWindow(windowHandle);
        return 0;
    case WM_PAINT:
       hardwareDeviceContext = BeginPaint(windowHandle, &paintStruct);
       OnPaint(hardwareDeviceContext);
       EndPaint(windowHandle, &paintStruct);
       return 0;
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    default:
        return DefWindowProc(windowHandle, windowMessage, windowParameters, lParameters);
    }
}

HWND CreateOpenGLWindow(char* title, int x, int y, int width, int height, BYTE type, DWORD flags){
    int         n, pf;
    HWND        hWnd;
    WNDCLASS    wc;
    LOGPALETTE* lpPal;
    PIXELFORMATDESCRIPTOR pfd;
    static HINSTANCE hInstance = 0;

    /* only register the window class once - use hInstance as a flag. */
    if (!hInstance) {
	hInstance = GetModuleHandle(NULL);
	wc.style         = CS_OWNDC;
	wc.lpfnWndProc   = (WNDPROC)windowCallbackFunction;
	wc.cbClsExtra    = 0;
	wc.cbWndExtra    = 0;
	wc.hInstance     = hInstance;
	wc.hIcon         = LoadIcon(NULL, IDI_WINLOGO);
	wc.hCursor       = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = NULL;
	wc.lpszMenuName  = NULL;
	wc.lpszClassName = "OpenGL";

	if (!RegisterClass(&wc)) {
	    MessageBox(NULL, "RegisterClass() failed:  "
		       "Cannot register window class.", "Error", MB_OK);
	    return NULL;
	}
    }

    hWnd = CreateWindow("OpenGL", title, WS_OVERLAPPEDWINDOW |
			WS_CLIPSIBLINGS | WS_CLIPCHILDREN,
			x, y, width, height, NULL, NULL, hInstance, NULL);

    if (hWnd == NULL) {
	MessageBox(NULL, "CreateWindow() failed:  Cannot create a window.",
		   "Error", MB_OK);
	return NULL;
    }

    hardwareDeviceContext = GetDC(hWnd);

    /* there is no guarantee that the contents of the stack that become
       the pfd are zeroed, therefore _make sure_ to clear these bits. */
    memset(&pfd, 0, sizeof(pfd));
    pfd.nSize        = sizeof(pfd);
    pfd.nVersion     = 1;
    pfd.dwFlags      = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | flags;
    pfd.iPixelType   = type;
    pfd.cDepthBits   = 32;
    pfd.cColorBits   = 32;

    pf = ChoosePixelFormat(hardwareDeviceContext, &pfd);
    if (pf == 0) {
	MessageBox(NULL, "ChoosePixelFormat() failed:  "
		   "Cannot find a suitable pixel format.", "Error", MB_OK);
	return 0;
    }

    if (SetPixelFormat(hardwareDeviceContext, pf, &pfd) == FALSE) {
	MessageBox(NULL, "SetPixelFormat() failed:  "
		   "Cannot set format specified.", "Error", MB_OK);
	return 0;
    }

    DescribePixelFormat(hardwareDeviceContext, pf, sizeof(PIXELFORMATDESCRIPTOR), &pfd);

    if (pfd.dwFlags & PFD_NEED_PALETTE ||
	pfd.iPixelType == PFD_TYPE_COLORINDEX) {

	n = 1 << pfd.cColorBits;
	if (n > 256) n = 256;

	lpPal = (LOGPALETTE*)malloc(sizeof(LOGPALETTE) +
				    sizeof(PALETTEENTRY) * n);
	memset(lpPal, 0, sizeof(LOGPALETTE) + sizeof(PALETTEENTRY) * n);
	lpPal->palVersion = 0x300;
	lpPal->palNumEntries = n;

	GetSystemPaletteEntries(hardwareDeviceContext, 0, n, &lpPal->palPalEntry[0]);

	/* if the pixel type is RGBA, then we want to make an RGB ramp,
	   otherwise (color index) set individual colors. */
	if (pfd.iPixelType == PFD_TYPE_RGBA) {
	    int redMask = (1 << pfd.cRedBits) - 1;
	    int greenMask = (1 << pfd.cGreenBits) - 1;
	    int blueMask = (1 << pfd.cBlueBits) - 1;
	    int i;

	    /* fill in the entries with an RGB color ramp. */
	    for (i = 0; i < n; ++i) {
		lpPal->palPalEntry[i].peRed =
		    (((i >> pfd.cRedShift)   & redMask)   * 255) / redMask;
		lpPal->palPalEntry[i].peGreen =
		    (((i >> pfd.cGreenShift) & greenMask) * 255) / greenMask;
		lpPal->palPalEntry[i].peBlue =
		    (((i >> pfd.cBlueShift)  & blueMask)  * 255) / blueMask;
		lpPal->palPalEntry[i].peFlags = 0;
	    }
	} else {
	    lpPal->palPalEntry[0].peRed = 0;
	    lpPal->palPalEntry[0].peGreen = 0;
	    lpPal->palPalEntry[0].peBlue = 0;
	    lpPal->palPalEntry[0].peFlags = PC_NOCOLLAPSE;
	    lpPal->palPalEntry[1].peRed = 255;
	    lpPal->palPalEntry[1].peGreen = 0;
	    lpPal->palPalEntry[1].peBlue = 0;
	    lpPal->palPalEntry[1].peFlags = PC_NOCOLLAPSE;
	    lpPal->palPalEntry[2].peRed = 0;
	    lpPal->palPalEntry[2].peGreen = 255;
	    lpPal->palPalEntry[2].peBlue = 0;
	    lpPal->palPalEntry[2].peFlags = PC_NOCOLLAPSE;
	    lpPal->palPalEntry[3].peRed = 0;
	    lpPal->palPalEntry[3].peGreen = 0;
	    lpPal->palPalEntry[3].peBlue = 255;
	    lpPal->palPalEntry[3].peFlags = PC_NOCOLLAPSE;
	}

	hPalette = CreatePalette(lpPal);
	if (hPalette) {
	    SelectPalette(hardwareDeviceContext, hPalette, FALSE);
	    RealizePalette(hardwareDeviceContext);
	}

	free(lpPal);
    }

    ReleaseDC(hWnd, hardwareDeviceContext);

    return hWnd;
}

WWindow::WWindow(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow){
    windowClass.cbSize        = sizeof(WNDCLASSEX);
    windowClass.style         = 0;
    windowClass.lpfnWndProc   = windowCallbackFunction;
    windowClass.cbClsExtra    = 0;
    windowClass.cbWndExtra    = 0;
    windowClass.hInstance     = 0;
    windowClass.hIcon         = LoadIcon(NULL, IDI_APPLICATION);
    windowClass.hCursor       = LoadCursor(NULL, IDC_ARROW);
    windowClass.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);
    windowClass.lpszMenuName  = NULL;
    windowClass.lpszClassName = g_szClassName;
    windowClass.hIconSm       = LoadIcon(NULL, IDI_APPLICATION);

    glEnable(GL_DEPTH_TEST);

    _Assert(RegisterClassEx(&windowClass), "Error registering window class.");

    // windowHandle = CreateWindowEx(
    //         WS_EX_CLIENTEDGE,
    //         g_szClassName,
    //         "Window Title",
    //         WS_SIZEBOX,
    //         CW_USEDEFAULT, CW_USEDEFAULT, 1920, 1080,
    //         NULL, NULL, hInstance, NULL
    // );

    DWORD buffer = PFD_DOUBLEBUFFER;	/* buffering type */
    BYTE  color  = PFD_TYPE_RGBA;	/* color type */

    windowHandle = CreateOpenGLWindow("mouse", 0, 0, 256, 256, color, buffer);

    _Assert(windowHandle, "Error creating window instance.");

    ShowWindow(windowHandle, nCmdShow);
    UpdateWindow(windowHandle);

    // Step 3: The Message Loop
    while(GetMessage(&windowMessage, NULL, 0, 0) > 0)
    {
        TranslateMessage(&windowMessage);
        DispatchMessage(&windowMessage);
    }
    // return windowMessage.wParam;
}

VOID OnPaint(HDC hardwareDeviceContext)
{

}
