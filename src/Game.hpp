#ifndef GAME_H
#define GAME_H

#include "Level.hpp"
#include "Actor.hpp"

// Forward declarations
class Level;

class Game {
public:
    enum GameState {
        Running, Paused, Exiting, WaitingForDraw
    };

    Game();

    void Start();
    void Run();
    void End();
    void notifyHasDrawn();

    void Draw();

    Actor CreateActor();

private:
    ActorManager actorManager;
    List<Level> levels;

    GameState currentGameState;
};

#endif
