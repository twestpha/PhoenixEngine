#ifndef TRANSFORM_COMPONENT_SYSTEM_H
#define TRANSFORM_COMPONENT_SYSTEM_H

#include <map>

#include "ComponentSystem.hpp"
#include "Math3D.hpp"
#include "Actor.hpp"

#define MAX_TRANSFORM_COMPONENTS 16

struct TransformComponentData {
    Vector3 position;
    Vector4 orientation;
    Vector3 scale;
};

class TransformComponentSystem : public ComponentSystem {
private:
    TransformComponentData components[MAX_TRANSFORM_COMPONENTS];

public:
    TransformComponentSystem();

    ComponentReference AddComponent(void* data);
    void Initialize();
    void Update();

    // void ApplyTransform(Actor actor);
};

#endif
