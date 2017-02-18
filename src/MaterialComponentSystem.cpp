#include <windows.h>
#include <GL/gl.h>
#include <GL/glu.h>

#include "MaterialComponentSystem.hpp"
#include "GLHelpers.hpp"
#include "Assert.hpp"
#include "Allocator.hpp"
#include "Level.hpp"
#include "Time.hpp"

// TODO yeah remove this temp shit later
float pixels[] = {
    0.0f, 0.0f, 0.0f,   1.0f, 1.0f, 1.0f,
    1.0f, 1.0f, 1.0f,   0.0f, 0.0f, 0.0f
};

MaterialComponentSystem::MaterialComponentSystem(){
    data.usedInstances = 0;
    data.allocatedInstances = 0;
    data.instanceBuffer = Allocator::Allocate(0);

    shaderProgram.InitializeFromData(/* TODO Fetch data from resource*/);
    //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    // https://open.gl/drawing
    //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

    // This really should be per-material, but fuck it for now
    // unsigned int colorbuffer;
    // GLHelper::glGenBuffers(1, &colorbuffer);
    // printf("Test Buffer Pointer: %d\n", colorbuffer);
    // GLHelper::glBindBuffers(GL_ARRAY_BUFFER, colorbuffer);
    // GLHelper::glBufferData(GL_ARRAY_BUFFER, sizeof(g_color_buffer_data), g_color_buffer_data, GL_STATIC_DRAW);
    // GLuint texture;
    // glGenTextures(1, &texture);
    // glBindTexture(GL_TEXTURE_2D, texture);
    //
    // glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 2, 2, 0, GL_RGB, GL_FLOAT, pixels);

}

void MaterialComponentSystem::Allocate(unsigned int size){
    Assert_(size > data.usedInstances, "Component system 'MaterialComponentSystem' trying to allocate less memory than it's already using\n");

    MaterialComponentData newData;

    const unsigned bytes = size * (sizeof(Actor));

    newData.instanceBuffer = Allocator::Allocate(bytes);

    newData.usedInstances = data.usedInstances;
    newData.allocatedInstances = size;

    newData.actor = (Actor*) newData.instanceBuffer;

    memcpy(newData.actor, data.actor, data.usedInstances * sizeof(Actor));

    Allocator::Deallocate(data.instanceBuffer);
    data = newData;
}

void MaterialComponentSystem::Initialize(Actor actor){
    MaterialComponentInstance instance = MakeInstance(data.usedInstances);
    data.usedInstances++;

    data.actor[instance.index] = actor;

    map[actor.id] = instance.index;
}

MaterialComponentInstance MaterialComponentSystem::MakeInstance(unsigned int index){
    return MaterialComponentInstance(index);
}

MaterialComponentInstance MaterialComponentSystem::GetInstanceForActor(Actor actor){
    return MakeInstance(map[actor.id]);
}

bool MaterialComponentSystem::HasComponentForActor(Actor actor){
    return map.find(actor.id) != map.end();
}

void MaterialComponentSystem::DestroyInstance(unsigned int index){
    unsigned int lastActorIndex = data.usedInstances - 1;
    Actor lastActor = data.actor[lastActorIndex];
    Actor actor = data.actor[index];

    data.actor[index] = data.actor[lastActorIndex];

    map[lastActor.id] = index;
    map.erase(actor.id);

    data.usedInstances--;
}

void MaterialComponentSystem::ApplyMaterial(Actor actor){
    shaderProgram.Apply();
}
