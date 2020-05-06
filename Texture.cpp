#include <iostream>
#include "texture_h.h"


Texture::Texture()
{       
    width = 0;
    height = 0;
    internalFormat = imageFormat = GL_RGB;
    wrapS = wrapT = GL_REPEAT;
    filterMin = filterMax = GL_LINEAR;
    glGenTextures(1, &this->Id);
}

void Texture::BindAsActive()
{
    glBindTexture(GL_TEXTURE_2D, this->Id);
}

void Texture::genTexture(GLuint width, GLuint height, unsigned char* tData)
{
    this->width = width;this->height = height;
    
    // Creating The Texture
    glBindTexture(GL_TEXTURE_2D, this->Id);
    glTexImage2D(GL_TEXTURE_2D, 0, this->internalFormat, width, height, 0, this->imageFormat, GL_UNSIGNED_BYTE, tData);
    
    // Setting the Texture's wrap and filter modes
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, this->wrapS);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, this->wrapT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, this->filterMin);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, this->filterMax);
    
    //Unbinding the texture
    glBindTexture(GL_TEXTURE_2D, 0);
}

