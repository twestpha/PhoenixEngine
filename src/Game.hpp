#pragma once

class Game {
public:
    static Game* Instance();

    void Draw();

    // Probably functions to add/remove stuff to renderer
private:
    Game();
    static Game* instancePointer;
};
