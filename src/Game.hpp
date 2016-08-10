#ifndef GAME_H
#define GAME_H

#include "Level.hpp"
#include "Actor.hpp"

// Forward declarations
class Level;

class Game {
public:
    Game();

    void Start();
    void Run();
    void End();
    void Unblock();

    void Draw();

    Actor CreateActor();

private:
    ActorManager actorManager;
    List<Level> levels;

    bool running;
    bool blocking;
};

#endif
