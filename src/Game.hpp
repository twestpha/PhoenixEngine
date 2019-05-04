#ifndef GAME_H
#define GAME_H

#include "Actor.hpp"
#include "Renderer.hpp"
#include "TransformComponentSystem.hpp"
#include "ModelComponentSystem.hpp"
#include "ResourceManager.hpp"

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

    TransformComponentSystem transformComponentSystem;
};

#endif
