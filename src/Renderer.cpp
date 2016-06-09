#include <stdio.h>

#include "Renderer.hpp"

Renderer* Renderer::instancePointer = 0;

Renderer* Renderer::Instance(){
    if(!instancePointer){
        instancePointer = new Renderer();
    }
    return instancePointer;
}

Renderer::Renderer(){

}

void Renderer::Draw(){
    while(true){
        printf("I'm drawing, threaded!\n");
    }
}
