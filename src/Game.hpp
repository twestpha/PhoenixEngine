#ifndef GAME_H
#define GAME_H

#include "Level.hpp"
#include "Actor.hpp"
#include "Renderer.hpp"

// Forward declarations
class Level;
class Renderer;

class Game {
    friend class Renderer;
public:
    enum GameState {
        Running, Paused, Exiting, WaitingForDraw
    };

    Game();
    ~Game();

    void Start();
    void Run();
    void End();
    void notifyHasDrawn();

    void Draw();

    Actor CreateActor();

private:
    Renderer* renderer;
    ActorManager actorManager;
    GameState currentGameState;

protected:
    List<Level> levels;
};

#endif
