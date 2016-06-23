#include "ComponentSystem.hpp"
#include "Vector.hpp"

#pragma once

struct TransformComponentInstance {
    // Vector3 position;
    // Vector3 scale;
    // Vector4 rotation;
};

struct TransformComponentData {

};

class TransformComponentSystem : public ComponentSystem {
public:
    TransformComponentSystem();
private:

};
