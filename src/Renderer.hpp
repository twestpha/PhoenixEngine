#ifndef RENDERER_H
#define RENDERER_H

#include "Game.hpp"

// Forward declarations
class Game;

class Renderer {
public:
    Renderer();

    void Draw(Game* game);
    void Shutdown();
private:
    unsigned long frameCount;
    double totalTime;
    double maxDrawTime;
};

#endif
