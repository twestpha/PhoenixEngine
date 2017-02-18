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
// Buffer Operations
typedef void (GLAPIENTRY* PFNGLGENBUFFERSPROC)(int number, unsigned int* buffer);
typedef void (GLAPIENTRY* PFNGLBINDBUFFERARBPROC)(GLenum target, unsigned int buffer);
typedef void (GLAPIENTRY* PFNGLBUFFERDATAARBPROC)(GLenum target, unsigned int size, const void *data, GLenum usage);

// Shader Operations
typedef GLuint (GLAPIENTRY* PFNGLCREATESHADERPROC)(GLenum type);
typedef void (GLAPIENTRY* PFNGLSHADERSOURCEPROC)(GLuint shader, unsigned int count, const char *const* string, const int* length);
typedef void (GLAPIENTRY* PFNGLCOMPILESHADERPROC)(GLuint shader);
typedef void (GLAPIENTRY* PFNGLGETSHADERIVPROC)(GLuint shader, GLenum pname, int* parameter);
typedef void (GLAPIENTRY* PFNGLGETSHADERINFOLOGPROC)(GLuint shader, unsigned int bufferSize, unsigned int* length, char* infoLog);

// Shader Program Operations
typedef GLuint (GLAPIENTRY* PFNGLCREATEPROGRAMPROC)(void);
typedef void (GLAPIENTRY* PFNGLGETATTACHEDSHADERSPROC)(GLuint program, GLsizei maxCount, GLsizei* count, GLuint* shaders);
typedef void (GLAPIENTRY* PFNGLBINDFRAGDATALOCATIONPROC)(GLuint program, GLuint colorNumber, const GLchar* name);
typedef void (GLAPIENTRY* PFNGLLINKPROGRAMPROC)(GLuint program);
typedef void (GLAPIENTRY* PFNGLUSEPROGRAMPROC)(GLuint program);

//####################################################################################################################################
// Namespace function declarations
//####################################################################################################################################
// Buffer Operations
extern PFNGLGENBUFFERSPROC glGenBuffers;
extern PFNGLBINDBUFFERARBPROC glBindBuffers;
extern PFNGLBUFFERDATAARBPROC glBufferData;

// Shader Operations
extern PFNGLCREATESHADERPROC glCreateShader;
extern PFNGLSHADERSOURCEPROC glShaderSource;
extern PFNGLCOMPILESHADERPROC glCompileShader;
extern PFNGLGETSHADERIVPROC glGetShaderiv;
extern PFNGLGETSHADERINFOLOGPROC glGetShaderInfoLog;

// Shader Program Operations
extern PFNGLCREATEPROGRAMPROC glCreateProgram;
extern PFNGLATTACHSHADERPROC glAttachShader;
extern PFNGLBINDFRAGDATALOCATIONPROC glBindFragDataLocation;
extern PFNGLLINKPROGRAMPROC glLinkProgram;
extern PFNGLUSEPROGRAMPROC glUseProgram;

//####################################################################################################################################
// Initialization
//####################################################################################################################################
bool GLHelperInitialize();

} // namespace GLHelper

#endif /* GL_HELPERS_H */
