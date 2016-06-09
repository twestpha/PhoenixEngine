#include <stdio.h>

#include "Game.hpp"

Game* Game::instancePointer = 0;

Game* Game::Instance(){
    if(!instancePointer){
        instancePointer = new Game();
    }
    return instancePointer;
}

Game::Game(){

}

void Game::Draw(){
    while(true){
        printf("I'm Ticking, threaded!\n");
    }
}
