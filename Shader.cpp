#include<iostream>
#include "shader_h.h"

using namespace glm;

void Shader::Build(const GLchar* vertexShaderSource, const GLchar* fragmentShaderSource) {

    
    //Building the Vertex Shader
    GLuint sVertex;
    sVertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(sVertex, 1, &vertexShaderSource, NULL);
    glCompileShader(sVertex);
    checkErrorsInCompilation(sVertex, SHADER_T::VERTEX_SHADER);
    
    //Building the Fragment Shader
    GLuint sFragment;
    sFragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(sFragment, 1, &fragmentShaderSource, NULL);
    glCompileShader(sFragment);
    checkErrorsInCompilation(sFragment, SHADER_T::FRAGMENT_SHADER);

    //Building the Shader Program
    this->shaderId = glCreateProgram();
    glAttachShader(this->shaderId, sVertex);
    glAttachShader(this->shaderId, sFragment);
    glLinkProgram(this->shaderId);
    checkErrorsInCompilation(this->shaderId, SHADER_T::SHADER_PROGRAM);
    
    //Now since the program is created, I can delete the shaders
    glDeleteShader(sVertex);
    glDeleteShader(sFragment);


}

void Shader::equipShaderWhenSetting(GLboolean equipShader) {
    if(equipShader) { this->Equip(); }
}

void Shader::setFloat(const GLchar* name, GLfloat value, GLboolean equipShader)
{
    equipShaderWhenSetting(equipShader);
    glUniform1f(glGetUniformLocation(this->shaderId, name), value);
}
void Shader::setInteger(const GLchar* name, GLint value, GLboolean equipShader)
{
    equipShaderWhenSetting(equipShader);
    glUniform1i(glGetUniformLocation(this->shaderId, name), value);
}
void Shader::setVector2f(const GLchar* name, GLfloat x, GLfloat y, GLboolean equipShader)
{
    equipShaderWhenSetting(equipShader);
    glUniform2f(glGetUniformLocation(this->shaderId, name), x, y);
}
void Shader::setVector2f(const GLchar* name, const vec2& value, GLboolean equipShader)
{
    equipShaderWhenSetting(equipShader);
    glUniform2f(glGetUniformLocation(this->shaderId, name), value.x, value.y);
}
void Shader::setVector3f(const GLchar* name, GLfloat x, GLfloat y, GLfloat z, GLboolean equipShader)
{
    equipShaderWhenSetting(equipShader);
    glUniform3f(glGetUniformLocation(this->shaderId, name), x, y, z);
}
void Shader::setVector3f(const GLchar* name, const vec3& value, GLboolean equipShader)
{
    equipShaderWhenSetting(equipShader);
    glUniform3f(glGetUniformLocation(this->shaderId, name), value.x, value.y, value.z);
}
void Shader::setVector4f(const GLchar* name, GLfloat x, GLfloat y, GLfloat z, GLfloat w, GLboolean equipShader)
{
    equipShaderWhenSetting(equipShader);
    glUniform4f(glGetUniformLocation(this->shaderId, name), x, y, z, w);
}
void Shader::setVector4f(const GLchar* name, const vec4& value, GLboolean equipShader)
{
    equipShaderWhenSetting(equipShader);
    glUniform4f(glGetUniformLocation(this->shaderId, name), value.x, value.y, value.z, value.w);
}
void Shader::setMatrix4(const GLchar* name, const mat4& matrix, GLboolean equipShader)
{
    equipShaderWhenSetting(equipShader);
    glUniformMatrix4fv(glGetUniformLocation(this->shaderId, name), 1, GL_FALSE, value_ptr(matrix));
}

string Shader::shaderTypeStringFromEnum(SHADER_T type) {
    string ret;
    switch (type)
    {
    case SHADER_T::VERTEX_SHADER:
        ret = "VERTEX";
        break;
    case SHADER_T::FRAGMENT_SHADER:
        ret = "FRAGMENT";
        break;
    case SHADER_T::SHADER_PROGRAM:
        ret = "PROGRAM";
        break;
    default:
        break;
    }
    return ret;
}
void Shader::checkErrorsInCompilation(GLuint shader, SHADER_T type)
{
    GLint success;
    GLchar infoLog[1024];
    if (type != SHADER_T::SHADER_PROGRAM)
    {
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(shader, sizeof(infoLog), NULL, infoLog);
            std::cout << "SHADER: Compilation failure. Type: " << shaderTypeStringFromEnum(type) << "\n"
                << infoLog<< std::endl;
        }
    }
    else
    {
        glGetProgramiv(shader, GL_LINK_STATUS, &success);
        if (!success)
        {
            glGetProgramInfoLog(shader, sizeof(infoLog), NULL, infoLog);
            std::cout << "SHADER: Linking failure. Type: " << shaderTypeStringFromEnum(type) << "\n"
                << infoLog<< std::endl;
        }
    }
}

Shader& Shader::Equip() {
    glUseProgram(this->shaderId);
    return *this;
}