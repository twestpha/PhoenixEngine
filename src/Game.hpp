#include "Actor.hpp"
#include "List.hpp"
#include "ComponentSystem.hpp"
#include "TransformComponentSystem.hpp"

#pragma once

class Game {
public:
    Game();
    void Start();
    void End();
private:
    TransformComponentSystem transformComponentSystem;



    bool running;
};
