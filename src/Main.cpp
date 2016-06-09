#include <thread>

#include "WWindow.hpp"

HINSTANCE hInstance;
HINSTANCE hPrevInstance;
HDC hardwareDeviceContext;
LPSTR lpCmdLine;
int nCmdShow;
bool winapi;

int TMain(){
    // setup game state here...

    if(winapi){
        // Arguments
        // LPWSTR *szArgList;
        // int argCount;
        //
        //  szArgList = CommandLineToArgvW(GetCommandLine(), &argCount);
        //  if (szArgList == NULL)
        //  }
        //  {
        //      MessageBox(NULL, L"Unable to parse command line", L"Error", MB_OK);
        //      return 10;
        //  }
        //
        //  for(int i = 0; i < argCount; i++)
        //  {
        //      MessageBox(NULL, szArgList[i], L"Arglist contents", MB_OK);
        // }

        WWindow w(0, 0, 256, 256, "Test Window");
    } else {
        // Linux window implementation goes here :D
    }



    return 0;
}

int WINAPI WinMain(HINSTANCE _hInstance, HINSTANCE _hPrevInstance, LPSTR _lpCmdLine, int _nCmdShow){
    hInstance = _hInstance;
    hPrevInstance = _hPrevInstance;
    lpCmdLine = _lpCmdLine;
    nCmdShow = _nCmdShow;
    winapi = true;
    return TMain();
}
