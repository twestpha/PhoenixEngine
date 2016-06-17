#include "Actor.hpp"
#include "List.hpp"
#include "ComponentSystem.hpp"

#pragma once

class Game {
public:
    Game();
    void Start();
    void End();
private:
    // For now, just a list of actors and components. Later, list of levels.
    List<Actor> actorList;
    List<ComponentSystem> componentSystems;

    bool running;
};
