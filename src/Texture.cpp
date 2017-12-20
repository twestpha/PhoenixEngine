#include "Texture.hpp"

Texture::Texture(){
    GLHelper::glGenTextures(1, &textureRef);
    GLHelper::glBindTexture(GL_TEXTURE_2D, textureRef);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // glGenerateMipmap(GL_TEXTURE_2D);
}

unsigned int Texture::GetTextureRef(){
    return textureRef;
}

void Texture::InitializeFromData(void* data){
    // glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 2, 2, 0, GL_RGB, GL_FLOAT, pixels);
}
