#ifndef MATERIAL_COMPONENT_SYSTEM_H
#define MATERIAL_COMPONENT_SYSTEM_H

#include <windows.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <map>

#include "Texture.hpp"
#include "Actor.hpp"
#include "ShaderProgram.hpp"

// Forward declarations

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
    // Honestly, it's going to be a bunch of pointers
    // probably the shader program to use
    // also various textures
    // should the textures be fixed...? Probably not, but it's quite tempting
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

private:
    MaterialComponentData data;
    std::map<unsigned int, unsigned int> map;

    ShaderProgram shaderProgram; // TODO is this the best way to do this...? Probably should be per-material...
    // Also per-material textures but yeah...
    Texture* texture;
};

#endif
