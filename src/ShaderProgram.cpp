#include "ShaderProgram.hpp"

using namespace GLHelper;

// TODO Holy shit tech debt
const char* RAW_VERTEX_SHADER = "\
in vec2 position;\
\
void main()\
{\
    gl_Position = gl_ProjectionMatrix * gl_ModelViewMatrix * gl_Vertex;\
}\
";

const char* RAW_FRAGMENT_SHADER = "\
#version 140\n\
\
out vec4 outColor;\
\
void main()\
{\
    outColor = vec4(1.0, 1.0, 1.0, 1.0);\
}\
";

#define INVALID_SHADER_REF -1
#define SHADER_COUNT 1
#define SHADER_LENGTH NULL
#define SHADER_ERROR_LENGTH 512

const char* vertexErrorPrint = "Vertex";
const char* fragmentErrorPrint = "Fragment";

Shader::Shader(){
    shaderRef = INVALID_SHADER_REF;
}

void Shader::InitializeFromData(void* data, ShaderType type){
    this->data = data;
    this->type = type;

    shaderRef = glCreateShader(type);
    glShaderSource(shaderRef, SHADER_COUNT, GetShaderSource(), SHADER_LENGTH);
    glCompileShader(shaderRef);

    GLint compiled = GL_FALSE;
    glGetShaderiv(shaderRef, GL_COMPILE_STATUS, &compiled);

    if(compiled == GL_FALSE){
        char message[SHADER_ERROR_LENGTH];
        glGetShaderInfoLog(shaderRef, SHADER_ERROR_LENGTH, NULL, message);
        const char* typeErrorPrint = (type == VertexShaderType) ? vertexErrorPrint : fragmentErrorPrint;
        Assert_(false, "%s Shader failed to compile with message:\n%s", typeErrorPrint, message);
    }

    // TODO Enable after data is mutable and not a const string
    // Allocator::Deallocate(data);
}

GLint Shader::GetShaderRef(){
    return shaderRef;
}

const char* const* Shader::GetShaderSource(){
    return (const char* const*) data;
}

ShaderProgram::ShaderProgram(){

}

void ShaderProgram::InitializeFromData(/*void* data*/){
    vertexShader.InitializeFromData((void*) &RAW_VERTEX_SHADER, VertexShaderType);
    fragmentShader.InitializeFromData((void*) &RAW_FRAGMENT_SHADER, FragmentShaderType);

    // attach vertex and fragment shaders
    shaderProgramRef = glCreateProgram();
    glAttachShader(shaderProgramRef, vertexShader.GetShaderRef());
    glAttachShader(shaderProgramRef, fragmentShader.GetShaderRef());

    // bind fragment data location
    glBindFragDataLocation(shaderProgramRef, 0, "outColor");

    // Link the vertex and fragment shader into a shader program
    glLinkProgram(shaderProgramRef);
}

void ShaderProgram::BindAttribute(ShaderType type, const char* attributename) {
    // Specify the layout of the vertex data
    // GLint posAttrib = glGetAttribLocation(shaderProgram, "position");
    // glEnableVertexAttribArray(posAttrib);
    // glVertexAttribPointer(posAttrib, 2, GL_FLOAT, GL_FALSE, 0, 0);
}


void ShaderProgram::Apply(){
    glUseProgram(shaderProgramRef);
}
