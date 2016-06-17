#include "Game.hpp"

Game::Game(){
    running = true;
}

void Game::Start(){
    while(running){
        printf("Game state running threaded!\n");
        // Update all the shit
    }
}

void Game::End(){
    running = false;
}
