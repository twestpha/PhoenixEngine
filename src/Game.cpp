#include "Game.hpp"

Game::Game(){
    running = true;

    // Create 5 test actors
    ActorManager::Instance()->createActor();
    ActorManager::Instance()->createActor();
    ActorManager::Instance()->createActor();
    ActorManager::Instance()->createActor();
    ActorManager::Instance()->createActor();
}

void Game::Start(){
    // Setup runtime threads

    while(running){
        // Update all the shit

    }
}

void Game::End(){
    running = false;
}
