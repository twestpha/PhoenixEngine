#include "GLHelpers.hpp"

namespace GLHelper {

//####################################################################################################################################
// Namespace function declarations
//####################################################################################################################################
PFNGLGENBUFFERSPROC glGenBuffers = NULL;

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
    printf("Initializing GL version %s\n", glGetString(GL_VERSION));
    bool result = false;

    glGenBuffers = (PFNGLGENBUFFERSPROC)GLHelperGetProcAddress("glGenBuffers");
    result = result || (glGenBuffers != NULL);
    Assert_(glGenBuffers, "glGenBuffers Failed to Initialize.");

    printf("%p\n", glGenBuffers);

    return result;
}

} // namespace GLHelper
