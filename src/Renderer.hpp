#pragma once

class Renderer {
public:
    static Renderer* Instance();

    void Draw();

    // Probably functions to add/remove stuff to renderer
private:
    Renderer();
    static Renderer* instancePointer;
};
