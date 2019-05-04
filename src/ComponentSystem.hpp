#ifndef COMPONENT_SYSTEM_H
#define COMPONENT_SYSTEM_H

#include "Assert.hpp"

// Forward declarations
class Game;

enum ComponentType {
    ECompTransform,
    ECompModel,
};

struct ComponentReference {
    ComponentType type;
    int ActorName; // just for now
    int ComponentIndex;
};

class ComponentSystem {
private:
    Game* game;
    ComponentType type;

    int enabled;
    int count;

public:
    ComponentSystem(){
        enabled = 0;
        count = 0;
    }

    void Initialize(){}
    void Update(){}

    ComponentReference AddComponent(void* data){
        Assert_(false, "Add Component failed");
    };

    void SetGame(Game* g){
        game = g;
    }
};

#endif // COMPONENT_SYSTEM_H
