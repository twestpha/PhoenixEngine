#include <thread>

#include "Game.hpp"
#include "Time.hpp"
#include "Level.hpp"

Game::Game(){
    running = true;

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

    while(running){
        blocking = true;

        for(int i(0); i < levels.Used(); ++i){
            levels[i].Update();
        }

        Time::UpdatelastFrameTime();
        while(blocking){
            std::this_thread::yield();
        }
    }
}

void Game::End(){
    Unblock();
    running = false;
}

void Game::Unblock(){
    blocking = false;
}

void Game::Draw(){
    for(int i(0); i < levels.Used(); ++i){
        levels[i].modelComponentSystem.Draw();
    }
}

Actor Game::CreateActor(){
    return actorManager.CreateActor();
}
