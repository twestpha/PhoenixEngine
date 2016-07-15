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
public:
    TransformComponentSystem transformComponentSystem;
    ModelComponentSystem modelComponentSystem;
    bool running;
};
