#include <thread>

#include "Renderer.hpp"
#include "Game.hpp"
#include "Flags.hpp"

#pragma once

const int kErrorCode = 1;
const int kNoErrorCode = 0;

class Engine {
public:
    Engine(const char* arguments[]);
    void Run();
    int GetExitCode();
private:
    Flags errorFlags;

    std::thread RendererThread;
    std::thread GameThread;
};
