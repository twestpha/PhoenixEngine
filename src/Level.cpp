#include "Level.hpp"

#include "Math3D.hpp"
#include "ResourceManager.hpp"

Level::Level(){
    running = true;

    // Create test actors
    Actor testActor = ActorManager::Instance()->createActor();

    transformComponentSystem.Allocate(1); // TODO don't leave this a magic number
    modelComponentSystem.Allocate(1); // ""

    // Test model
    Model* model = new Model();
    ResourceManager::Instance()->loadModelFromFile("highpoly.phx", model);

    ResourceManager::Instance()->Join(); // Close all loading threads running

    transformComponentSystem.Initialize(testActor, Vector3(0.0f, 0.0f, 0.0f), Vector3(1.0f, 1.0f, 1.0f), Vector4(0.0f, 0.0f, 0.0f, 0.0f));
    modelComponentSystem.Initialize(testActor, *model);
}

void Level::Start(){
    // Setup runtime threads

    while(running){
        // Update all the components
    }
}

void Level::End(){
    running = false;
}
