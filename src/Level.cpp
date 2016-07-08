#include "Level.hpp"

#include "Math3D.hpp"
#include "ResourceManager.hpp"

Level::Level(){
    running = true;

    // Create test actors
    Actor testActor = ActorManager::Instance()->createActor();

    transformComponentSystem.Allocate(1); // TODO don't leave this a magic number
    modelComponentSystem.Allocate(1);

    Model model;
    Model model2;

    ResourceManager::Instance()->loadModelFromFile("cube.phx", &model);
    // ResourceManager::Instance()->loadModelFromFile("cube.dae", &model2);

    ResourceManager::Instance()->Join(); // Close all loading threads running

    transformComponentSystem.Initialize(testActor, Vector3(0.0f, 0.0f, 0.0f), Vector3(1.0f, 1.0f, 1.0f), Vector4(0.0f, 0.0f, 0.0f, 0.0f));
    modelComponentSystem.Initialize(testActor, 0);
}

void Level::Start(){
    // Setup runtime threads

    while(running){
        // Update all the shit
    }
}

void Level::End(){
    running = false;
}
