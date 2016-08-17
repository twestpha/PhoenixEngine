#ifndef MODEL_COMPONENT_SYSTEM_H
#define MODEL_COMPONENT_SYSTEM_H

#include <map>

#include "Math3D.hpp"
#include "Actor.hpp"
#include "Model.hpp"

// TODO Implement Static Models
// https://open.gl/drawing

// Forward declarations
class Level;

struct ModelComponentInstance {
    unsigned int index;

    ModelComponentInstance(unsigned int index){
        this->index = index;
    }
};

struct ModelComponentData {
    unsigned int usedInstances;
    unsigned int allocatedInstances;
    void *instanceBuffer;

    Actor* actor;
    Model* model;
};

class ModelComponentSystem {
public:
    ModelComponentSystem();
    void Allocate(unsigned int size);

    void Initialize(Actor actor, Model model);

    ModelComponentInstance MakeInstance(unsigned int index);
    ModelComponentInstance GetInstanceForActor(Actor actor);

    void DestroyInstance(unsigned int index);

    // Drawing Methods
    void Draw(Actor actor);
    int UsedInstances();
    Actor GetActorForIndex(int index);

    Level* level;
private:
    ModelComponentData data;
    std::map<unsigned int, unsigned int> map;
};

#endif
