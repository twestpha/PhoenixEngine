#include "Engine.hpp"

Engine::Engine(const char* arguments[]) : RendererThread(), GameThread() {
    // commandline arguments go here... not sure what I'll need

    // setup rendering window and stuff (might get this passed in, not sure yet)
}

void Engine::Run(){
    Renderer *renderer = Renderer::Instance();
    Game *game = Game::Instance();

    RendererThread = std::thread(Renderer::Draw, renderer);
    GameThread = std::thread(Game::Draw, game);

    while(!errorFlags.HasError()){

    }
}

int Engine::GetExitCode(){
    return errorFlags.HasError() ? kErrorCode : kNoErrorCode;
}
