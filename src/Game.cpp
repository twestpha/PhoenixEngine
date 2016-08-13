#include <thread>

#include "Game.hpp"
#include "Time.hpp"
#include "Level.hpp"

Game::Game(){
    currentGameState = Running;

    Level* testLevel = new Level();
    testLevel->game = this;
    testLevel->Initialize();
    levels.Add(*testLevel);
}

void Game::Start(){
    Run();
}

void Game::Run(){
    Time::UpdatelastFrameTime();

    while(currentGameState != Exiting){
        currentGameState = WaitingForDraw;

        for(int i(0); i < levels.Used(); ++i){
            levels[i].Update();
        }

        Time::UpdatelastFrameTime();
        while(currentGameState == WaitingForDraw){
            std::this_thread::yield();
        }
    }
}

void Game::End(){
    currentGameState = Exiting;
}

void Game::notifyHasDrawn(){
    currentGameState = Running;
}

void Game::Draw(){
    for(int i(0); i < levels.Used(); ++i){
        levels[i].modelComponentSystem.Draw();
    }
}

Actor Game::CreateActor(){
    return actorManager.CreateActor();
}
