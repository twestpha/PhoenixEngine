#ifndef LEVEL_H
#define LEVEL_H

#include "Actor.hpp"
#include "Game.hpp"
#include "List.hpp"
#include "TransformComponentSystem.hpp"
#include "ModelComponentSystem.hpp"

// Forward declarations
class Game;

class Level {
public:
    Game* game;

    Level();

    void Initialize();
    void Update();

    TransformComponentSystem transformComponentSystem;
    ModelComponentSystem modelComponentSystem;
};

#endif
