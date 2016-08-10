#include "Game.hpp"
#include "Time.hpp"

Game::Game(){
    running = true;

    Level* testLevel = new Level();
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
        while(blocking){} // yeah this is shit
    }
}

void Game::End(){
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
