#include "Actor.hpp"
#include "List.hpp"
#include "TransformComponentSystem.hpp"
#include "ModelComponentSystem.hpp"

#ifndef LEVEL_H
#define LEVEL_H

class Level {
public:
    Level();
    void Start();
    void End();

    TransformComponentSystem transformComponentSystem;
    ModelComponentSystem modelComponentSystem;

    bool running;
};

#endif
