#include "TransformComponentSystem.hpp"
#include "Assert.hpp"
#include "Allocator.hpp"

TransformComponentSystem::TransformComponentSystem(){
    data.usedInstances = 0;
    data.allocatedInstances = 0;
    data.instanceBuffer = Allocator::Allocate(0);
}

void TransformComponentSystem::Allocate(unsigned int size){
    _Assert(size > data.usedInstances, "Component system 'TransformComponentSystem' trying to allocate less memory than it's already using\n");

    TransformComponentData newData;

    const unsigned bytes = size * (sizeof(Actor) + 2 * sizeof(Vector3) + sizeof(Vector4));

    newData.instanceBuffer = Allocator::Allocate(bytes);

    newData.usedInstances = data.usedInstances;
    newData.allocatedInstances = size;

    newData.actor = (Actor*) newData.instanceBuffer;
    newData.position = (Vector3*) newData.actor + size;
    newData.scale = (Vector3*) newData.position + size;
    newData.rotation = (Vector4*) newData.scale + size;

    memcpy(newData.actor, data.actor, data.usedInstances * sizeof(Actor));
    memcpy(newData.position, data.position, data.usedInstances * sizeof(Vector3));
    memcpy(newData.scale, data.scale, data.usedInstances * sizeof(Vector3));
    memcpy(newData.rotation, data.rotation, data.usedInstances * sizeof(Vector4));

    Allocator::Deallocate(data.instanceBuffer);
    data = newData;
}

void TransformComponentSystem::Initialize(Actor actor, Vector3 position, Vector3 scale, Vector4 rotation){
    TransformComponentInstance instance = MakeInstance(data.usedInstances);
    data.usedInstances++;

    data.actor[instance.index] = actor;
    data.position[instance.index] = position;
    data.scale[instance.index] = scale;
    data.rotation[instance.index] = rotation;

    map[actor] = instance.index;
}

TransformComponentInstance TransformComponentSystem::MakeInstance(unsigned int index){
    return TransformComponentInstance(index);
}

TransformComponentInstance TransformComponentSystem::GetInstanceForActor(Actor actor){
    return MakeInstance(map[actor]);
}

void TransformComponentSystem::DestroyInstance(unsigned int index){
    unsigned int lastActorIndex = data.usedInstances - 1;
    Actor lastActor = data.actor[lastActorIndex];
    Actor actor = data.actor[index];

    data.actor[index] = data.actor[lastActorIndex];
    data.position[index] = data.position[lastActorIndex];
    data.scale[index] = data.scale[lastActorIndex];
    data.rotation[index] = data.rotation[lastActorIndex];

    map[lastActor] = index;
    map.erase(actor);

    data.usedInstances--;
}
