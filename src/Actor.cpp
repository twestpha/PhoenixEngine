#include "Actor.hpp"

ActorManager* ActorManager::instancePointer;

ActorManager* ActorManager::Instance(){
    if(!instancePointer){
        instancePointer = new ActorManager();
    }
    return instancePointer;
}

ActorManager::ActorManager(){
    for(int i(0); i < MINIMUM_FREE_INDICES; i++){ // TODO MAGIC NUMBERWANG
        freeIndices.Add(i);
    }
}

Actor ActorManager::createActor(){
    unsigned int index;
    if(freeIndices.Used() > MINIMUM_FREE_INDICES){
        index = freeIndices[0];
        freeIndices.Remove(0);
    } else {
        generation.Add(0);
        index = generation.Used() - 1;
        _Assert(index < ACTOR_INDEX_MASK + 1, "Allocating actor index is too large.");
    }

    return Actor(index, generation[index]);
}

bool ActorManager::Alive(Actor actor){
    return generation[actor.index()] == actor.generation();
}

void ActorManager::Destroy(Actor& actor){
    const unsigned int index = actor.index();
    generation.At(generation[index] + 1, index);
    freeIndices.Add(index);
}
