#ifndef GL_HELPERS_H
#define GL_HELPERS_H

#include <windows.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glext.h>

#include "Assert.hpp"

// https://www.opengl.org/wiki/Load_OpenGL_Functions
namespace GLHelper {
//####################################################################################################################################
// API Entry Setup
//####################################################################################################################################
#ifdef APIENTRY
    #ifndef GLAPIENTRY
        #define GLAPIENTRY APIENTRY
    #endif
#else
    #if defined(__MINGW32__) || defined(__CYGWIN__) || (_MSC_VER >= 800) || defined(_STDCALL_SUPPORTED) || defined(__BORLANDC__)
        #define APIENTRY __stdcall
        #ifndef GLAPIENTRY
            #define GLAPIENTRY __stdcall
        #endif
    #else
        #define APIENTRY
    #endif
#endif

//####################################################################################################################################
// Get Proc Setup
//####################################################################################################################################
#ifdef _WIN32
    #define GLHelperGetProcAddress(name) wglGetAnyProcAddress(name)
#else /* Linux */
    #define GLHelperGetProcAddress(name) (*glXGetProcAddressARB)(name)
#endif /* _WIN32 */

void* wglGetAnyProcAddress(const char *name);

//####################################################################################################################################
// Function Type definitions
//####################################################################################################################################
typedef void (GLAPIENTRY* PFNGLGENBUFFERSPROC)(GLsizei n, GLuint* buffers);

//####################################################################################################################################
// Namespace function declarations
//####################################################################################################################################
extern PFNGLGENBUFFERSPROC glGenBuffers;

//####################################################################################################################################
// Initialization
//####################################################################################################################################
bool GLHelperInitialize();

} // namespace GLHelper

#endif /* GL_HELPERS_H */
