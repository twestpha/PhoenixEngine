#ifndef TRANSFORM_COMPONENT_SYSTEM_H
#define TRANSFORM_COMPONENT_SYSTEM_H

#include <map>

#include "Math3D.hpp"
#include "Actor.hpp"

// Forward declarations
class Level;

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

    void Initialize(Actor actor, Vector3 position, Vector3 scale, Vector4 rotation);

    TransformComponentInstance MakeInstance(unsigned int index);
    TransformComponentInstance GetInstanceForActor(Actor actor);
    bool HasComponentForActor(Actor actor);
    void DestroyInstance(unsigned int index);

    void ApplyTransform(Actor actor);

    Level* level;
private:
    TransformComponentData data;
    std::map<unsigned int, unsigned int> map;
};

#endif
