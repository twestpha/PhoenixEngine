#include <windows.h>
#include <GL/gl.h>
#include <GL/glu.h>

#include "ModelComponentSystem.hpp"
#include "Assert.hpp"
#include "Allocator.hpp"

ModelComponentSystem::ModelComponentSystem(){
    data.usedInstances = 0;
    data.allocatedInstances = 0;
    data.instanceBuffer = Allocator::Allocate(0);
}

void ModelComponentSystem::Allocate(unsigned int size){
    _Assert(size > data.usedInstances, "Component system 'ModelComponentSystem' trying to allocate less memory than it's already using\n");

    ModelComponentData newData;

    const unsigned bytes = size * sizeof(Actor);

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

    map[actor] = instance.index;
}

ModelComponentInstance ModelComponentSystem::MakeInstance(unsigned int index){
    return ModelComponentInstance(index);
}

ModelComponentInstance ModelComponentSystem::GetInstanceForActor(Actor actor){
    return MakeInstance(map[actor]);
}

void ModelComponentSystem::DestroyInstance(unsigned int index){
    unsigned int lastActorIndex = data.usedInstances - 1;
    Actor lastActor = data.actor[lastActorIndex];
    Actor actor = data.actor[index];

    data.actor[index] = data.actor[lastActorIndex];

    map[lastActor] = index;
    map.erase(actor);

    data.usedInstances--;
}

void ModelComponentSystem::Draw(){
    for(int i(0); i < data.usedInstances; ++i){
        Model model = Model(data.model[i]);
        void* vertices = model.GetData();
        int vertexCount = model.vertexCount;

        // Fuck it, access memory directly I guess
        for(int j(0); j < vertexCount * 8; j+=8){
            float x = ((float*)vertices)[j + 0];
            float y = ((float*)vertices)[j + 1];
            float z = ((float*)vertices)[j + 2];
            float nx = ((float*)vertices)[j + 3];
            float ny = ((float*)vertices)[j + 4];
            float nz = ((float*)vertices)[j + 5];
            float u = ((float*)vertices)[j + 6];
            float v = ((float*)vertices)[j + 7];

            glVertex3f(x, y, z);
        }
    }
}
