#include "Assert.hpp"
#include "List.hpp"

#pragma once

// Code from http://bitsquid.blogspot.com/2014/08/building-data-oriented-entity-system.html
const unsigned ENTITY_INDEX_BITS = 22;
const unsigned ENTITY_INDEX_MASK = (1<<ENTITY_INDEX_BITS)-1;

const unsigned ENTITY_GENERATION_BITS = 8;
const unsigned ENTITY_GENERATION_MASK = (1<<ENTITY_GENERATION_BITS)-1;

const unsigned MINIMUM_FREE_INDICES = 1024;

struct Actor {
 unsigned id;

 unsigned index() const {return id & ENTITY_INDEX_MASK;}
 unsigned generation() const {return (id >> ENTITY_INDEX_BITS) & ENTITY_GENERATION_MASK;}
};

class ActorManager {
public:
    static ActorManager* instancePointer;
    static ActorManager* Instance();

    Actor createActor();
    bool Alive(Actor actor);
    void Destroy(Actor& actor);
private:
    ActorManager();

    List<unsigned int> generation;
    List<unsigned int> freeIndices;
};
