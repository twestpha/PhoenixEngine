#ifndef TRANSFORM_COMPONENT_SYSTEM_H
#define TRANSFORM_COMPONENT_SYSTEM_H

#include <map>

#include "Math3D.hpp"
#include "Actor.hpp"

// Forward declarations
class Level;

struct TransformComponentInstance {
    unsigned index;

    TransformComponentInstance(unsigned index){
        this->index = index;
    }
};

struct TransformComponentData {
    unsigned usedInstances;
    unsigned allocatedInstances;
    void *instanceBuffer;

    Actor* actor;
    Vector3* position;
    Vector3* scale;
    Vector4* rotation;
};

class TransformComponentSystem {
public:
    TransformComponentSystem();
    void Allocate(unsigned size);

    void Initialize(Actor actor, Vector3 position, Vector3 scale, Vector4 rotation);

    TransformComponentInstance MakeInstance(unsigned index);
    TransformComponentInstance GetInstanceForActor(Actor actor);
    bool HasComponentForActor(Actor actor);
    void DestroyInstance(unsigned index);

    void ApplyTransform(Actor actor);

    void Update();

    Level* level;
private:
    TransformComponentData data;
    std::map<unsigned, unsigned> map;
};

#endif
