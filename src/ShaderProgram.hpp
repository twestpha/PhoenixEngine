#ifndef SHADER_PROGRAM_H
#define SHADER_PROGRAM_H

#include "Resource.hpp"
#include "GLHelpers.hpp"
#include "Allocator.hpp"

enum ShaderType {
    VertexShaderType = GL_VERTEX_SHADER,
     FragmentShaderType = GL_FRAGMENT_SHADER
};

class Shader : public Resource {
public:
    Shader();

    GLint GetShaderRef();
    void InitializeFromData(void* data, ShaderType type);
private:
    const char* const* GetShaderSource();
    GLint shaderRef;
    ShaderType type;
};

class ShaderProgram {
public:
    ShaderProgram();

    void InitializeFromData(/*void* data*/);

    void Apply();
private:
    Shader vertexShader;
    Shader fragmentShader;

    GLint shaderProgramRef;
};

#endif
