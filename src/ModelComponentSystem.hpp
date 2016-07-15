#include <map>

#include "Math3D.hpp"
#include "Actor.hpp"
#include "Model.hpp"

#pragma once

struct ModelComponentInstance {
    unsigned int index;

    ModelComponentInstance(unsigned int index){
        this->index = index;
    }
};

struct ModelComponentData {
    unsigned int usedInstances;
    unsigned int allocatedInstances;
    void *instanceBuffer;

    Actor* actor;
    Model* model;
};

class ModelComponentSystem {
public:
    ModelComponentSystem();
    void Allocate(unsigned int size);

    void Initialize(Actor actor, Model model);

    ModelComponentInstance MakeInstance(unsigned int index);
    ModelComponentInstance GetInstanceForActor(Actor actor);

    void DestroyInstance(unsigned int index);

    void Draw();
private:
    ModelComponentData data;
    std::map<Actor, unsigned int> map;
};
