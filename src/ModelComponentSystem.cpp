#include <windows.h>
#include <GL/gl.h>
#include <GL/glu.h>

#include "ModelComponentSystem.hpp"
#include "Assert.hpp"
#include "Allocator.hpp"
#include "Level.hpp"

ModelComponentSystem::ModelComponentSystem(){
    data.usedInstances = 0;
    data.allocatedInstances = 0;
    data.instanceBuffer = Allocator::Allocate(0);
}

void ModelComponentSystem::Allocate(unsigned int size){
    Assert_(size > data.usedInstances, "Component system 'ModelComponentSystem' trying to allocate less memory than it's already using\n");

    ModelComponentData newData;

    const unsigned bytes = size * (sizeof(Actor) + sizeof(Model));

    newData.instanceBuffer = Allocator::Allocate(bytes);

    newData.usedInstances = data.usedInstances;
    newData.allocatedInstances = size;

    newData.actor = (Actor*) newData.instanceBuffer;
    newData.model = (Model*) newData.actor + size;

    memcpy(newData.actor, data.actor, data.usedInstances * sizeof(Actor));
    memcpy(newData.model, data.model, data.usedInstances * sizeof(Model));

    Allocator::Deallocate(data.instanceBuffer);
    data = newData;
}

void ModelComponentSystem::Initialize(Actor actor, Model model){
    ModelComponentInstance instance = MakeInstance(data.usedInstances);
    data.usedInstances++;

    data.actor[instance.index] = actor;
    data.model[instance.index] = model;

    // Requirements
    Assert_(level->transformComponentSystem.HasComponentForActor(actor), "Actor '%s' does not have transform component.", actor.String());
    Assert_(level->materialComponentSystem.HasComponentForActor(actor), "Actor '%s' does not have material component.", actor.String());

    map[actor.id] = instance.index;
}

ModelComponentInstance ModelComponentSystem::MakeInstance(unsigned int index){
    return ModelComponentInstance(index);
}

ModelComponentInstance ModelComponentSystem::GetInstanceForActor(Actor actor){
    return MakeInstance(map[actor.id]);
}

void ModelComponentSystem::DestroyInstance(unsigned int index){
    unsigned int lastActorIndex = data.usedInstances - 1;
    Actor lastActor = data.actor[lastActorIndex];
    Actor actor = data.actor[index];

    data.actor[index] = data.actor[lastActorIndex];

    map[lastActor.id] = index;
    map.erase(actor.id);

    data.usedInstances--;
}

void ModelComponentSystem::Draw(Actor actor){
    // TODO Change to use vertex buffer objects (VBO's)

    // Need reference to vertex memory
    // GLuint vbo;
    // glGenBuffers(1, &vbo);
    // glBindBuffer(GL_ARRAY_BUFFER, vbo);
    // glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    // Note static draw                                          ^
    // Also can use:
    // GL_STATIC_DRAW
    // GL_DYNAMIC_DRAW
    // GL_STREAM_DRAW

    // From c2_triangle
    // GLuint vao; // Do we need VAO's? What do these do?
    // glGenVertexArrays(1, &vao);
    // glBindVertexArray(vao);

    // GLuint vbo;
    // glGenBuffers(1, &vbo);
    //
    // GLfloat vertices[] = {
    //      0.0f,  0.5f,
    //      0.5f, -0.5f,
    //     -0.5f, -0.5f
    // };
    //
    // glBindBuffer(GL_ARRAY_BUFFER, vbo);
    // glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    ModelComponentInstance instance = map[actor.id];
    Model model = data.model[instance.index];
    Vertex* vertices = model.GetData();
    int vertexCount = model.vertexCount;

    glBegin(GL_TRIANGLES);
        for(int i(0); i < vertexCount; ++i){
            Vertex vertex = vertices[i];

            glVertex3f(vertex.position.x, vertex.position.y, vertex.position.z);
            glNormal3f(vertex.normal.x, vertex.normal.y, vertex.normal.z);
            glTexCoord2f(vertex.uvcoord.x, vertex.uvcoord.y);
        }
    glEnd();
}

int ModelComponentSystem::UsedInstances(){
    return data.usedInstances;
}

Actor ModelComponentSystem::GetActorForIndex(int index){
    return (Actor) data.actor[index];
}
