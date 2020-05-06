#pragma once

#include <glew.h>
#include <glm/glm.hpp>

#include "texture_h.h"
#include "renderer_h.h"

//Basically, an encapsulation for an in-game entity
class GameObj {

public:
    
    vec2   pos, size, velocity;
    GLfloat     rotation;
    vec3   color;
    GLboolean   isSolid;
    GLboolean   isDestroyed;
    Texture   texture;

    GameObj(); //The default constructor 
    GameObj(vec2 pos, vec2 size, Texture sprite, vec3 color = vec3(1.0f), vec2 velocity = vec2(0.0f, 0.0f));
    
    // for drawing the sprite
    virtual void Draw(RendererSprite& renderer);
};