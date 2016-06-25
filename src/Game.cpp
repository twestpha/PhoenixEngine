#include "Game.hpp"
#include "Math3D.hpp"

Game::Game(){
    running = true;

    // Create test actors
    Actor demoActor = ActorManager::Instance()->createActor();
    Actor demoActor1 = ActorManager::Instance()->createActor();
    Actor demoActor2 = ActorManager::Instance()->createActor();

    transformComponentSystem.Allocate(3); // TODO don't leave this a magic number

    transformComponentSystem.Initialize(demoActor, Vector3(0.0f, 0.0f, 0.0f), Vector3(1.0f, 1.0f, 1.0f), Vector4(0.0f, 0.0f, 0.0f, 0.0f));
    transformComponentSystem.Initialize(demoActor1, Vector3(1.0f, 1.0f, 1.0f), Vector3(1.0f, 1.0f, 1.0f), Vector4(0.0f, 0.0f, 0.0f, 0.0f));
    transformComponentSystem.Initialize(demoActor2, Vector3(-1.0f, -1.0f, -1.0f), Vector3(1.0f, 1.0f, 1.0f), Vector4(0.0f, 0.0f, 0.0f, 0.0f));
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
