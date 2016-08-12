#ifndef MATERIAL_COMPONENT_SYSTEM_H
#define MATERIAL_COMPONENT_SYSTEM_H

#include <map>

#include "Actor.hpp"

// Forward declarations
class Level;

struct MaterialComponentInstance {
    unsigned int index;

    MaterialComponentInstance(unsigned int index){
        this->index = index;
    }
};

struct MaterialComponentData {
    unsigned int usedInstances;
    unsigned int allocatedInstances;
    void *instanceBuffer;

    Actor* actor;
    // Arrays of data
};

class MaterialComponentSystem {
public:
    MaterialComponentSystem();
    void Allocate(unsigned int size);

    void Initialize(Actor actor);

    MaterialComponentInstance MakeInstance(unsigned int index);
    MaterialComponentInstance GetInstanceForActor(Actor actor);
    bool HasComponentForActor(Actor actor);
    void DestroyInstance(unsigned int index);

    void ApplyMaterial(Actor actor);

    Level* level;
private:
    MaterialComponentData data;
    std::map<unsigned int, unsigned int> map;
};

#endif