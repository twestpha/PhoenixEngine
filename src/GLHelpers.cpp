#include "GLHelpers.hpp"

namespace GLHelper {

//####################################################################################################################################
// Namespace function declarations
//####################################################################################################################################
// Buffer Operations
PFNGLGENBUFFERSPROC glGenBuffers = NULL;
PFNGLBINDBUFFERARBPROC glBindBuffers = NULL;
PFNGLBUFFERDATAARBPROC glBufferData = NULL;

// Shader Operations
PFNGLCREATESHADERPROC glCreateShader = NULL;
PFNGLSHADERSOURCEPROC glShaderSource = NULL;
PFNGLCOMPILESHADERPROC glCompileShader = NULL;
PFNGLGETSHADERIVPROC glGetShaderiv = NULL;
PFNGLGETSHADERINFOLOGPROC glGetShaderInfoLog = NULL;

// Shader Program Operations
PFNGLCREATEPROGRAMPROC glCreateProgram = NULL;
PFNGLATTACHSHADERPROC glAttachShader = NULL;
PFNGLBINDFRAGDATALOCATIONPROC glBindFragDataLocation = NULL;
PFNGLLINKPROGRAMPROC glLinkProgram = NULL;
PFNGLUSEPROGRAMPROC glUseProgram = NULL;

// Texture Operations
PFNGLGENTEXTURESPROC glGenTextures = NULL;
PFNGLBINDTEXTURESPROC glBindTexture = NULL;

//####################################################################################################################################
// Get Proc Setup
//####################################################################################################################################
void* wglGetAnyProcAddress(const char* name){
    void* pointer = (void*) wglGetProcAddress(name);
    if(pointer == 0 || (pointer == (void*)0x1) || (pointer == (void*)0x2) || (pointer == (void*)0x3) || (pointer == (void*)-1) ){
        WriteWarning_("wglGetAnyProcAddress(%s) failed, trying to GetProcAddress from opengl32.dll", name);
        HMODULE module = LoadLibraryA("opengl32.dll");
        pointer = (void*) GetProcAddress(module, name);
    }

    return pointer;
}

//####################################################################################################################################
// Initialization
//####################################################################################################################################
bool GLHelperInitialize(){
    // Buffer Operations
    glGenBuffers = (PFNGLGENBUFFERSPROC)GLHelperGetProcAddress("glGenBuffers");
    glBindBuffers = (PFNGLBINDBUFFERARBPROC)GLHelperGetProcAddress("glBindBufferARB");
    glBufferData = (PFNGLBUFFERDATAARBPROC)GLHelperGetProcAddress("glBufferDataARB");
    bool bufferOperationResult = glGenBuffers && glBindBuffers && glBufferData;

    // Shader Operations
    glCreateShader = (PFNGLCREATESHADERPROC)GLHelperGetProcAddress("glCreateShader");
    glShaderSource = (PFNGLSHADERSOURCEPROC)GLHelperGetProcAddress("glShaderSource");
    glCompileShader = (PFNGLCOMPILESHADERPROC)GLHelperGetProcAddress("glCompileShader");
    glGetShaderiv = (PFNGLGETSHADERIVPROC)GLHelperGetProcAddress("glGetShaderiv");
    glGetShaderInfoLog = (PFNGLGETSHADERINFOLOGPROC)GLHelperGetProcAddress("glGetShaderInfoLog");
    bool shaderOperationResult = glCreateShader && glShaderSource && glCompileShader && glGetShaderiv && glGetShaderInfoLog;

    // Shader Program Operations
    glCreateProgram = (PFNGLCREATEPROGRAMPROC)GLHelperGetProcAddress("glCreateProgram");
    glAttachShader = (PFNGLATTACHSHADERPROC)GLHelperGetProcAddress("glAttachShader");
    glBindFragDataLocation = (PFNGLBINDFRAGDATALOCATIONPROC)GLHelperGetProcAddress("glBindFragDataLocation");
    glLinkProgram = (PFNGLLINKPROGRAMPROC)GLHelperGetProcAddress("glLinkProgram");
    glUseProgram = (PFNGLUSEPROGRAMPROC)GLHelperGetProcAddress("glUseProgram");
    bool shaderProgramOperationResult = glCreateProgram && glAttachShader && glBindFragDataLocation && glLinkProgram && glUseProgram;

    // Texture Operations
    glGenTextures = (PFNGLGENTEXTURESPROC)GLHelperGetProcAddress("glGenTextures");
    glBindTexture = (PFNGLBINDTEXTURESPROC)GLHelperGetProcAddress("glBindTexture");
    bool textureOperationResult = glGenTextures  && glBindTexture;

    return bufferOperationResult && shaderOperationResult && shaderProgramOperationResult && textureOperationResult;
}

} // namespace GLHelper
