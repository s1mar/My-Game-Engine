#include "particle_h.h"



ParticleEmitter::ParticleEmitter(Shader shader, Texture texture, GLuint amount)
    : shader(shader), texture(texture), amountOfParticles(amount)
{
    this->init();
}

void ParticleEmitter::Update(GLfloat delta, GameObj& object, GLuint newParticles, vec2 offset)
{
    // adding new particles 
    for (GLuint i = 0; i < newParticles; ++i)
    {
        int unusedParticle = this->firstUnusedParticle();
        this->respawnParticle(this->particles[unusedParticle], object, offset);
    }
    // updating all particles
    for (GLuint i = 0; i < this->amountOfParticles; ++i)
    {
        Particle& p = this->particles[i];
        p.ttl -= delta; // reduce life
        if (p.ttl > 0.0f)
        {	// particle is alive, thus update
            p.position -= p.velocity * delta;
            p.color.a -= delta * 2.5f;
        }
    }
}

// rendering the particles
void ParticleEmitter::Draw()
{
    //Using additive blending to give it a 'glow' effect
    glBlendFunc(GL_SRC_ALPHA, GL_ONE);
    this->shader.Equip();
    for (Particle particle : this->particles)
    {
        if (particle.ttl > 0.0f)
        {
            this->shader.setVector2f(SHADER_VAR_OFFSET, particle.position);
            this->shader.setVector4f(SHADER_VAR_COLOR, particle.color);
            this->texture.BindAsActive();
            glBindVertexArray(this->VAO);
            glDrawArrays(GL_TRIANGLES, 0, 6);
            glBindVertexArray(0);
        }
    }
    // Reseting to default blending mode after drawing
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void ParticleEmitter::init()
{
    // set up mesh and attribute properties
    unsigned int VBO;
    float particle_quad[] = {
        0.0f, 1.0f, 0.0f, 1.0f,
        1.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 0.0f,

        0.0f, 1.0f, 0.0f, 1.0f,
        1.0f, 1.0f, 1.0f, 1.0f,
        1.0f, 0.0f, 1.0f, 0.0f
    };
    glGenVertexArrays(1, &this->VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(this->VAO);
    // filling the mesh buffer
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(particle_quad), particle_quad, GL_STATIC_DRAW);
    // setting the mesh attributes
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
    glBindVertexArray(0);

    
    for (GLuint i = 0; i < this->amountOfParticles; ++i)
    {
        Particle* particle = new Particle();
        this->particles.push_back(*particle);
    }
}

// Storing the index of the last particle used (This is for quick access to the next dead particle)
GLuint particleLastUsed = 0;
GLuint ParticleEmitter::firstUnusedParticle()
{
    // first-search from last used particle
    for (GLuint i = particleLastUsed; i < this->amountOfParticles; ++i) {
        if (this->particles[i].ttl <= 0.0f) {
            particleLastUsed = i;
            return i;
        }
    }
    // otherwise doing a linear search
    for (GLuint i = 0; i < particleLastUsed; ++i) {
        if (this->particles[i].ttl <= 0.0f) {
            particleLastUsed = i;
            return i;
        }
    }
   
    particleLastUsed = 0;
    return 0;
}

void ParticleEmitter::respawnParticle(Particle& particle, GameObj& object, vec2 offset)
{
    float random = ((rand() % 100) - 50) / 10.0f;
    float color = 0.5f + ((rand() % 100) / 100.0f);
    particle.position = object.pos + random + offset;
    particle.color = vec4(color, color, color, 1.0f);
    particle.ttl = 1.0f;
    particle.velocity = object.velocity * 0.1f;
}