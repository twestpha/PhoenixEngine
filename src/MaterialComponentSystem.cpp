#include <windows.h>
#include <GL/gl.h>
#include <GL/glu.h>

#include "MaterialComponentSystem.hpp"
#include "GLHelpers.hpp"
#include "Assert.hpp"
#include "Allocator.hpp"
#include "Level.hpp"
#include "Time.hpp"

// One color for each vertex. They were generated randomly.
static const GLfloat g_color_buffer_data[] = {
    0.583f,  0.771f,  0.014f,
    0.609f,  0.115f,  0.436f,
    0.327f,  0.483f,  0.844f,
    0.822f,  0.569f,  0.201f,
    0.435f,  0.602f,  0.223f,
    0.310f,  0.747f,  0.185f,
    0.597f,  0.770f,  0.761f,
    0.559f,  0.436f,  0.730f,
    0.359f,  0.583f,  0.152f,
    0.483f,  0.596f,  0.789f,
    0.559f,  0.861f,  0.639f,
    0.195f,  0.548f,  0.859f,
    0.014f,  0.184f,  0.576f,
    0.771f,  0.328f,  0.970f,
    0.406f,  0.615f,  0.116f,
    0.676f,  0.977f,  0.133f,
    0.971f,  0.572f,  0.833f,
    0.140f,  0.616f,  0.489f,
    0.997f,  0.513f,  0.064f,
    0.945f,  0.719f,  0.592f,
    0.543f,  0.021f,  0.978f,
    0.279f,  0.317f,  0.505f,
    0.167f,  0.620f,  0.077f,
    0.347f,  0.857f,  0.137f,
    0.055f,  0.953f,  0.042f,
    0.714f,  0.505f,  0.345f,
    0.783f,  0.290f,  0.734f,
    0.722f,  0.645f,  0.174f,
    0.302f,  0.455f,  0.848f,
    0.225f,  0.587f,  0.040f,
    0.517f,  0.713f,  0.338f,
    0.053f,  0.959f,  0.120f,
    0.393f,  0.621f,  0.362f,
    0.673f,  0.211f,  0.457f,
    0.820f,  0.883f,  0.371f,
    0.982f,  0.099f,  0.879f
};

MaterialComponentSystem::MaterialComponentSystem(){
    data.usedInstances = 0;
    data.allocatedInstances = 0;
    data.instanceBuffer = Allocator::Allocate(0);

    unsigned int testBufferPointer;
    GLHelper::GenerateBuffers(1, &testBufferPointer);
    printf("Test Buffer Pointer: %d\n", testBufferPointer);
    // glBindBuffer
    // glBufferData

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
    // Nothing yet
}
