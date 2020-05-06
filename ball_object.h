#pragma once
#include <glew.h>
#include <glm/glm.hpp>
#include "texture_h.h"
#include "renderer_h.h"
#include "game_obj_h.h"
#include "constants_h.h"

class BallObj : public GameObj
{
public:
    	
    GLfloat   radius;
    GLboolean isStuck;

    BallObj();
    BallObj(vec2 position, GLfloat radius, vec2 velocity, Texture texture);
    
    vec2 Move(GLfloat delta, GLuint windowWidth,GameObj* paddle=nullptr);
    void Reset(vec2 position, vec2 velocity);
};