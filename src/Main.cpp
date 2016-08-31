#include "CompileOptions.hpp"

#include <thread>

#include "WWindow.hpp"
#include "Game.hpp"
#include "List.hpp"

bool winapi;

int TMain(){

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


    Game *game = new Game();
    std::thread gameThread(Game::Start, game);

    if(winapi){
        WWindow::Instance()->game = game;
        WWindow::Instance()->Start();
    } else {
        // Linux window implementation goes here :D
    }

    gameThread.join();

    return 0;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow){
    printf("-- Phoenix Engine --\n");
    WWindow::Instance()->hInstance     = hInstance;
    WWindow::Instance()->hPrevInstance = hPrevInstance;
    WWindow::Instance()->lpCmdLine     = lpCmdLine;
    WWindow::Instance()->nCmdShow      = nCmdShow;
    winapi = true;
    return TMain();
}
