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

    memcpy(newData.actor, data.actor, data.usedInstances * sizeof(Actor));

    Allocator::Deallocate(data.instanceBuffer);
    data = newData;
}

void ModelComponentSystem::Initialize(Actor actor, int test){
    ModelComponentInstance instance = MakeInstance(data.usedInstances);
    data.usedInstances++;

    data.actor[instance.index] = actor;

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
