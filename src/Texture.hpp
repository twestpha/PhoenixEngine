#ifndef TEXTURE_H
#define TEXTURE_H

#include "Resource.hpp"
#include "GLHelpers.hpp"
#include "Allocator.hpp"

class Texture : public Resource {
public:
    Texture();

    unsigned int GetTextureRef();
    void InitializeFromData(void* data);
private:
    GLuint textureRef;

};

#endif
