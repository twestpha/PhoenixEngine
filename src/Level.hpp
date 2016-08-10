#include "Actor.hpp"
#include "List.hpp"
#include "TransformComponentSystem.hpp"
#include "ModelComponentSystem.hpp"

#ifndef LEVEL_H
#define LEVEL_H

class Level {
public:
    Level();
    void Update();

    TransformComponentSystem transformComponentSystem;
    ModelComponentSystem modelComponentSystem;
};

#endif
