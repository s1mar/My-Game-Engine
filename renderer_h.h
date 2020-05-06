#pragma once
#include"shader_h.h"
#include"texture_h.h"
#include"constants_h.h"

class RendererSprite {

public:
    RendererSprite(Shader& shader) { this->shader = shader; this->initializeRenderData(); };
    ~RendererSprite() { glDeleteVertexArrays(1, &this->VAO); };

    void Draw(Texture& texture, vec2 pos,
        vec2 size = vec2(10, 10), GLfloat rot = 0.0f,
        vec3 color = vec3(1.0f)) {

        // Preparing the transformations
        this->shader.Equip();
        mat4 model = mat4(1.0f);

        model = translate(model, vec3(pos, 0.0f));

        model = translate(model, vec3(0.5f * size.x, 0.5f * size.y, 0.0f)); // translating the quad to the origin, so that the rotation in the next step is relative to the origin
        model = rotate(model, rot, vec3(0.0f, 0.0f, 1.0f));
        model = translate(model, vec3(-0.5f * size.x, -0.5f * size.y, 0.0f));

        model = scale(model, vec3(size, 1.0f));

        this->shader.setMatrix4(SHADER_MODEL, model);
        this->shader.setVector3f(SHADER_SPRITE_COLOR, color);

        glActiveTexture(GL_TEXTURE0);
        texture.BindAsActive();

        glBindVertexArray(this->VAO);
        glDrawArrays(GL_TRIANGLES, 0, 6);
        glBindVertexArray(0);

    }

private:
    Shader shader;
    GLuint VAO;
    void initializeRenderData() {

        GLuint VBO;
        GLfloat vertices[] = {
            // Pos      // Tex
            0.0f, 1.0f, 0.0f, 1.0f,
            1.0f, 0.0f, 1.0f, 0.0f,
            0.0f, 0.0f, 0.0f, 0.0f,

            0.0f, 1.0f, 0.0f, 1.0f,
            1.0f, 1.0f, 1.0f, 1.0f,
            1.0f, 0.0f, 1.0f, 0.0f
        };

        glGenVertexArrays(1, &this->VAO);
        glGenBuffers(1, &VBO);

        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

        glBindVertexArray(this->VAO);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (GLvoid*)0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
    }


};