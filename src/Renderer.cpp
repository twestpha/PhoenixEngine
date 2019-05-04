#include <windows.h>
#include <GL/gl.h>
#include <GL/glu.h>

#include "Renderer.hpp"
#include "Time.hpp"
#include "GLHelpers.hpp"

Renderer::Renderer(){
    maxDrawTime = 0.0f;
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
}

void Renderer::Draw(Game* game){
    double drawTime = Time::CurrentTime();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glPushMatrix();
        // for(int i(0); i < game->levels.Used(); ++i){
        //     Level& level = game->levels[i];
        //     int modelCount = level.ModelCount();
        //
        //     for(int j(0); j < modelCount; ++j){
        //         // Actor actor = level.modelComponentSystem.GetActorForIndex(j);
        //         glPushMatrix();
        //             // level.transformComponentSystem.ApplyTransform(actor);
        //             // level.modelComponentSystem.Draw(actor);
        //         glPopMatrix();
        //     }
        //     // printf("Size: %d, level: %p\n", sizeof(game->levels[i]), (Level*) &game->levels[i]);
        // }
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
