#include "Assert.hpp"
#include "List.hpp"

#ifndef ACTOR_H
#define ACTOR_H

// Code from http://bitsquid.blogspot.com/2014/08/building-data-oriented-entity-system.html
const unsigned ACTOR_INDEX_BITS = 22;
const unsigned ACTOR_INDEX_MASK = (1<<ACTOR_INDEX_BITS)-1;

const unsigned ACTOR_GENERATION_BITS = 8;
const unsigned ACTOR_GENERATION_MASK = (1<<ACTOR_GENERATION_BITS)-1;

const unsigned MINIMUM_FREE_INDICES = 1024;

struct Actor {
    unsigned id;

    unsigned index() const {return id & ACTOR_INDEX_MASK;}
    unsigned generation() const {return (id >> ACTOR_INDEX_BITS) & ACTOR_GENERATION_MASK;}

    bool operator<(const Actor otherActor) const{
        return this->index() < otherActor.index();
    }

    Actor(unsigned int index, unsigned int generation){
        this->id = (index << ACTOR_INDEX_BITS) | (generation & ACTOR_GENERATION_MASK);
    }
};

class ActorManager {
public:
    ActorManager();

    Actor CreateActor();
    bool Alive(Actor actor);
    void Destroy(Actor& actor);
private:
    List<unsigned int> generation;
    List<unsigned int> freeIndices;
};

#endif
