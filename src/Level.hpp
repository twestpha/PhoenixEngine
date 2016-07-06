#include "Actor.hpp"
#include "List.hpp"

#include "TransformComponentSystem.hpp"
#include "ModelComponentSystem.hpp"

#pragma once

class Level {
public:
    Level();
    void Start();
    void End();
private:
    TransformComponentSystem transformComponentSystem;
    ModelComponentSystem modelComponentSystem;
    bool running;
};
