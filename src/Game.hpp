#include "Actor.hpp"
#include "List.hpp"

#pragma once

class Game {
public:
    Game();
private:
    // For now, just a list of actors and components. Later, list of levels.
    List<Actor> actorList;
};
