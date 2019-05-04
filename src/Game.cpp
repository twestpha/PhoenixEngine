#include <thread>

#include "Game.hpp"
#include "Time.hpp"
#include "Renderer.hpp"

Game::Game(){
    currentGameState = Running;
    renderer = new Renderer();

    Actor testActor = CreateActor();

    transformComponentSystem.SetGame(this);
    transformComponentSystem.Initialize();

    // transformComponentSystem.Allocate(COMPONENT_MAXIMUM_PER_LEVEL);
    // modelComponentSystem.Allocate(COMPONENT_MAXIMUM_PER_LEVEL);
    // materialComponentSystem.Allocate(COMPONENT_MAXIMUM_PER_LEVEL);

    // transformComponentSystem.level = this;
    // modelComponentSystem.level = this;

    // Test model
    Model* model = new Model();
    ResourceManager::Instance()->loadModelFromFile("highpoly.phx", model);

    ResourceManager::Instance()->Join(); // Close all loading threads running

    // transformComponentSystem.Initialize(testActor, Vector3(0.0f, 0.0f, -6.0f), Vector3(1.0f, 1.0f, 1.0f), Vector4(0.0f, 0.0f, 1.0f, 0.0f));
    // materialComponentSystem.Initialize(testActor);
    // modelComponentSystem.Initialize(testActor, *model);
}

void Game::Start(){
    Run();
}

void Game::Run(){
    Time::UpdatelastFrameTime();

    while(currentGameState != Exiting){
        currentGameState = WaitingForDraw;



        Time::UpdatelastFrameTime();

        while(currentGameState == WaitingForDraw){
            std::this_thread::yield();
        }
    }
}

void Game::End(){
    renderer->Shutdown();
    currentGameState = Exiting;
}

void Game::notifyHasDrawn(){
    currentGameState = Running;
}

void Game::Draw(){
    renderer->Draw(this);
}

Actor Game::CreateActor(){
    return actorManager.CreateActor();
}
