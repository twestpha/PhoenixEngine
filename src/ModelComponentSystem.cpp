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

void ModelComponentSystem::Draw(){
    for(int i(0); i < data.usedInstances; ++i){
        Actor actor = Actor(data.actor[i]);
        Model model = Model(data.model[i]);
        Vertex* vertices = model.GetData();
        int vertexCount = model.vertexCount;

        glPushMatrix();
            level->transformComponentSystem.ApplyTransform(actor);

            glBegin(GL_TRIANGLES);
                for(int j(0); j < vertexCount; ++j){
                    Vertex vertex = vertices[j];

                    glVertex3f(vertex.position.x, vertex.position.y, vertex.position.z);
                    glNormal3f(vertex.normal.x, vertex.normal.y, vertex.normal.z);
                    glTexCoord2f(vertex.uvcoord.x, vertex.uvcoord.y);
                }
            glEnd();
        glPopMatrix();
    }
}
