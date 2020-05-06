#pragma once
#include <glm/glm.hpp>
#include <glew.h>
#include <vector>
#include "shader_h.h"
#include "texture_h.h"
#include "game_obj_h.h"

using namespace std;
using namespace glm;


class Particle {
public:
    vec2 position;
    vec2 velocity;
    vec4 color;
    GLfloat ttl; //time to live

    Particle() : ttl(0.0f), color(1.0f), velocity(0.0f), position(0.0f) {}

    void setColor(vec4 color){
        this->color = color;
    }
};


/* 
The ParticleEmitter class renders a large number of particles by repeatedly spawning and updating particles and killing 
them after their ttl(time-to-live) is up.
*/
class ParticleEmitter
{
public:
    
    ParticleEmitter(Shader shader, Texture texture, GLuint amount);
    // Rendering the particles
    void Draw();
    // Update particles
    void Update(GLfloat dt, GameObj& object, GLuint newParticles, vec2 offset = vec2(0.0f, 0.0f));
    
private:
   
    vector<Particle> particles;
    GLuint amountOfParticles;
    Shader shader;
    Texture texture;
    GLuint VAO;
    
    //To initialize the buffer and the vertex attributes
    void init();
    
    // Returns the first Particle index that's currently unused
    GLuint firstUnusedParticle();
    // To respawn particle
    void respawnParticle(Particle& particle, GameObj& object, vec2 offset = vec2(0.0f, 0.0f));
};