#include "GLHelpers.hpp"

namespace GLHelper {

//####################################################################################################################################
// Namespace function declarations
//####################################################################################################################################
GenerateBuffersFunctionPointer GenerateBuffers = NULL;

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
    bool result = false;

    GenerateBuffers = (GenerateBuffersFunctionPointer)GLHelperGetProcAddress("glGenBuffers");
    result = result || (GenerateBuffers != NULL);

    return result;
}

} // namespace GLHelper
