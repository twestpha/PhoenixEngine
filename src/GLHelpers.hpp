#ifndef GL_HELPERS_H
#define GL_HELPERS_H

#ifdef _WIN32
#define glewGetProcAddress(name) wglGetProcAddress((LPCSTR)name)
#else /* Linux */
#define glewGetProcAddress(name) (*glXGetProcAddressARB)(name)
#endif

// Readability Defines
#ifndef FunctionPointer
#define FunctionPointer APIENTRY
#endif

namespace GLHelper {

typedef void (FunctionPointer* GenerateBuffersFunctionSignature)(GLsizei n, GLuint* buffers);
static void (*GenerateBuffers)(int size, unsigned int* buffer);

static bool GLHelperInitialize(){
    bool result = false;

    result |= (GenerateBuffers = (GenerateBuffersFunctionSignature)glewGetProcAddress("glGenBuffers")) == NULL;

    return result;
}

} // Namespace GLHelper

#endif
