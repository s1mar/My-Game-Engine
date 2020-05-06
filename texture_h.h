#pragma once

#include<glew.h>


class Texture {

public:
    
    GLuint Id; // the id of the texture object
    // Texture dimensions
    GLuint width, height; // Width and height of the loaded image in pixels
    
    // The Texture Format
    GLuint internalFormat; //The format of the texture object
    GLuint imageFormat; //The format of the loaded image
    
    //Configuration
    GLuint wrapS; // Wrapping mode - S axis
    GLuint wrapT; // Wrapping mode - T axis

    GLuint filterMin; // Filtering mode if (texture pixels < screen pixels)
    GLuint filterMax; // Filtering mode if (texture pixels > screen pixels)
    
    Texture();
    
    // Generate texture from the image data
    void genTexture(GLuint width, GLuint height, unsigned char* data);
    
    // Binds the texture as the current active
    void BindAsActive();
};

