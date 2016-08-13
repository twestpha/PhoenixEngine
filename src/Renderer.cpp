#include <windows.h>
#include <GL/gl.h>
#include <GL/glu.h>

#include "Renderer.hpp"
#include "Time.hpp"

Renderer::Renderer(){
    maxDrawTime = 0.0f;
}

void Renderer::Draw(Game* game){
    double drawTime = Time::CurrentTime();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glPushMatrix();
        for(int i(0); i < game->levels.Used(); ++i){
            game->levels[i].modelComponentSystem.Draw();
            // NOT JUST MCS NOW
        }
    glPopMatrix();
    glFlush();
    drawTime = Time::TimeElapsed(drawTime);

    if(drawTime > maxDrawTime){
        maxDrawTime = drawTime;
    }

    frameCount++;
    totalTime += drawTime;
}

void Renderer::Shutdown(){
    printf("Average draw time: %f seconds (%f FPS)\n", totalTime/float(frameCount), float(frameCount)/totalTime);
    printf("Maximum draw time: %f seconds (%f FPS)\n", maxDrawTime, 1.0f/maxDrawTime);
}
