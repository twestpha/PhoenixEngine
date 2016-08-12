#include <windows.h>
#include <GL/gl.h>
#include <GL/glu.h>

#include "MaterialComponentSystem.hpp"
#include "Assert.hpp"
#include "Allocator.hpp"
#include "Level.hpp"
#include "Time.hpp"

MaterialComponentSystem::MaterialComponentSystem(){
    data.usedInstances = 0;
    data.allocatedInstances = 0;
    data.instanceBuffer = Allocator::Allocate(0);
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

