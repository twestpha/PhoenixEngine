#include "Actor.hpp"

ActorManager::ActorManager(){
    for(int i(0); i < MINIMUM_FREE_INDICES; i++){
        freeIndices.Add(i);
    }
}

Actor ActorManager::CreateActor(){
    unsigned int index;
    if(freeIndices.Used() > MINIMUM_FREE_INDICES){
        index = freeIndices[0];
        freeIndices.Remove(0);
    } else {
        generation.Add(0);
        index = generation.Used() - 1;
        Assert_(index < ACTOR_INDEX_MASK + 1, "Allocating actor index is too large.");
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
