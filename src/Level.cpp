#include "Level.hpp"

#include "Math3D.hpp"
#include "ResourceManager.hpp"

const int COMPONENT_MAXIMUM_PER_LEVEL = 1024;

Level::Level(){
    running = true;

    // Create test actors
    Actor testActor = ActorManager::Instance()->createActor();

    transformComponentSystem.Allocate(COMPONENT_MAXIMUM_PER_LEVEL);
    modelComponentSystem.Allocate(COMPONENT_MAXIMUM_PER_LEVEL);

    // Test model
    Model* model = new Model();
    ResourceManager::Instance()->loadModelFromFile("highpoly.phx", model);

    ResourceManager::Instance()->Join(); // Close all loading threads running?

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
