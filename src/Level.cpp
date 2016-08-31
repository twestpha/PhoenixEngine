#include "Level.hpp"
#include "Math3D.hpp"
#include "ResourceManager.hpp"
#include "Time.hpp"

#define COMPONENT_MAXIMUM_PER_LEVEL 1024

Level::Level(){
}

void Level::Initialize(){
    // Create test actors
    Actor testActor = game->CreateActor();

    transformComponentSystem.Allocate(COMPONENT_MAXIMUM_PER_LEVEL);
    modelComponentSystem.Allocate(COMPONENT_MAXIMUM_PER_LEVEL);

    transformComponentSystem.level = this;
    modelComponentSystem.level = this;

    // Test model
    Model* model = new Model();
    ResourceManager::Instance()->loadModelFromFile("cube.phx", model);

    ResourceManager::Instance()->Join(); // Close all loading threads running

    transformComponentSystem.Initialize(testActor, Vector3(0.0f, 0.0f, -6.0f), Vector3(1.0f, 1.0f, 1.0f), Vector4(0.0f, 0.0f, 1.0f, 0.0f));
    modelComponentSystem.Initialize(testActor, *model);
}

void Level::Update(){
    // update all comp sys's that need it
    transformComponentSystem.Update();
}

int Level::ModelCount(){
    return modelComponentSystem.UsedInstances();
}
