#include <map>

#include "Math3D.hpp"
#include "Actor.hpp"

#pragma once

struct TransformComponentInstance {
    unsigned int index;

    TransformComponentInstance(unsigned int index){
        this->index = index;
    }
};

struct TransformComponentData {
    unsigned int usedInstances;
    unsigned int allocatedInstances;
    void *instanceBuffer;

    Actor* actor;
    Vector3* position;
    Vector3* scale;
    Vector4* rotation;
};

class TransformComponentSystem {
public:
    TransformComponentSystem();
    void Allocate(unsigned int size);

    // Empty function for Transform CS - don't need to update anything.
    void Update(){}

    void Initialize(Actor actor, Vector3 position, Vector3 scale, Vector4 rotation);

    TransformComponentInstance MakeInstance(unsigned int index);
    TransformComponentInstance GetInstanceForActor(Actor actor);

    void DestroyInstance(unsigned int index);
private:
    TransformComponentData data;
    std::map<Actor, unsigned int> map;
};
