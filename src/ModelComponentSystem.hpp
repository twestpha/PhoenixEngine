#ifndef MODEL_COMPONENT_SYSTEM_H
#define MODEL_COMPONENT_SYSTEM_H

#include <map>

#include "Math3D.hpp"
#include "Actor.hpp"
#include "Model.hpp"

// TODO Implement Static (In rendering pipeline) Models
// https://open.gl/drawing
// TODO Also implement VBO's (Vertex Buffer Objects) because that serialization fast

// Forward declarations
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


private:
    ModelComponentData data;
    std::map<unsigned int, unsigned int> map;
};

#endif // MODEL_COMPONENT_SYSTEM_H
