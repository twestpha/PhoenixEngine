#include <windows.h>
#include <GL/gl.h>
#include <GL/glu.h>

#include "MaterialComponentSystem.hpp"
#include "GLHelpers.hpp"
#include "Assert.hpp"
#include "Allocator.hpp"
#include "Level.hpp"
#include "Time.hpp"

// TODO Holy shit tech debt
float pixels[] = {
    0.0f, 0.0f, 0.0f,   1.0f, 1.0f, 1.0f,
    1.0f, 1.0f, 1.0f,   0.0f, 0.0f, 0.0f
};

const char* RAW_VERTEX_SHADER = "\
in vec2 position;\
\
void main()\
{\
    gl_Position = vec4(position, 0.0, 1.0);\
}\
";

const char* RAW_FRAGMENT_SHADER = "\
#version 150\
\
out vec4 outColor;\
\
void main()\
{\
    outColor = vec4(1.0, 1.0, 1.0, 1.0);\
}\
";

GLint MaterialComponentSystem::vertexShader = 0;
GLint MaterialComponentSystem::fragmentShader = 0;

MaterialComponentSystem::MaterialComponentSystem(){
    data.usedInstances = 0;
    data.allocatedInstances = 0;
    data.instanceBuffer = Allocator::Allocate(0);

    // This really should be per-material, but fuck it for now
    // unsigned int colorbuffer;
    // GLHelper::glGenBuffers(1, &colorbuffer);
    // printf("Test Buffer Pointer: %d\n", colorbuffer);
    // GLHelper::glBindBuffers(GL_ARRAY_BUFFER, colorbuffer);
    // GLHelper::glBufferData(GL_ARRAY_BUFFER, sizeof(g_color_buffer_data), g_color_buffer_data, GL_STATIC_DRAW);
    // GLuint texture;
    // glGenTextures(1, &texture);
    // glBindTexture(GL_TEXTURE_2D, texture);
    //
    // glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 2, 2, 0, GL_RGB, GL_FLOAT, pixels);
    vertexShader = GLHelper::glCreateShader(GL_VERTEX_SHADER);
    GLHelper::glShaderSource(vertexShader, 1, &RAW_VERTEX_SHADER, NULL);
    GLHelper::glCompileShader(vertexShader);

    fragmentShader = GLHelper::glCreateShader(GL_FRAGMENT_SHADER);
    GLHelper::glShaderSource(fragmentShader, 1, &RAW_FRAGMENT_SHADER, NULL);
    GLHelper::glCompileShader(fragmentShader);
    // GLint status;
    // GLHelper::glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &status);
    // char buffer[512];
    // GLHelper::glGetShaderInfoLog(vertexShader, 512, NULL, buffer);
    // printf("%s\n", buffer);

    // GLuint shaderProgram = glCreateProgram();
    // glAttachShader(shaderProgram, vertexShader);
    // glAttachShader(shaderProgram, fragmentShader);

    // Not sure...
    // glBindFragDataLocation(shaderProgram, 0, "outColor");

    // glLinkProgram(shaderProgram);

    // PUT THIS IN WHERE YOU USE IT
    // glUseProgram(shaderProgram);

    // USING attributes in shaders
    // GLint posAttrib = glGetAttribLocation(shaderProgram, "position");
    // glVertexAttribPointer(posAttrib, 2, GL_FLOAT, GL_FALSE, 0, 0);
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
