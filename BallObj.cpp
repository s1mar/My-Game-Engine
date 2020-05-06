#include "ball_object.h"
#include "collision_manager.h"




BallObj::BallObj()
    : GameObj(), radius(RADIUS_BALL), isStuck(true) { }


BallObj::BallObj(vec2 pos, GLfloat radius, vec2 velocity, Texture texture)
    : GameObj(pos, vec2(radius * 2, radius * 2), texture, vec3(1.0f), velocity), radius(radius), isStuck(true) { }
   

vec2 BallObj::Move(GLfloat delta, GLuint windowWidth,GameObj* obj)
{
    // Only allowing movement if the ball isn't stuck to the paddle
    if (!this->isStuck)
    {
        this->pos += this->velocity * delta;
        
        // Out of bounds check, if it is then reverse the velocity and restore to the correct position

        if (this->pos.x <= 0.0f)
        {
            this->velocity.x = -this->velocity.x;
            this->pos.x = 0.0f;
        }
        else if (this->pos.x + this->size.x >= windowWidth)
        {
            this->velocity.x = -this->velocity.x;
            this->pos.x = windowWidth - this->size.x;
        }
        if (this->pos.y <= 0.0f)
        {
            this->velocity.y = -this->velocity.y;
            this->pos.y = 0.0f;
        }

    }
    return this->pos;
}

// Resets the ball to initial Stuck Position (if ball is outside window bounds)
void BallObj::Reset(vec2 position, vec2 velocity)
{
    this->pos = position;
    this->velocity = velocity;
    this->isStuck = true;
}