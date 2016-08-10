#include "Level.hpp"

#ifndef GAME_H
#define GAME_H

class Game {
public:
    Game();

    void Start();
    void Run();
    void End();
    void Unblock();

    void Draw();

private:
    List<Level> levels;

    bool running;
    bool blocking;
};

#endif
