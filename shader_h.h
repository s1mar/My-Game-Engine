#pragma once
#include <string>
#include<map>
#include<glew.h>
#include<glm/glm.hpp>
#include<glm/gtc/type_ptr.hpp>

using namespace std;
using namespace glm;


enum class SHADER_T {VERTEX_SHADER,FRAGMENT_SHADER,SHADER_PROGRAM};


class Shader {

public:

	GLuint shaderId;
    
    void Build(const GLchar* vertexShaderSource, const GLchar* fragmentShaderSource);

    void    setFloat(const GLchar* name, GLfloat value, GLboolean EquipShader = false);
    void    setInteger(const GLchar* name, GLint value, GLboolean EquipShader = false);
    void    setVector2f(const GLchar* name, GLfloat x, GLfloat y, GLboolean EquipShader = false);
    void    setVector2f(const GLchar* name, const vec2& value, GLboolean EquipShader = false);
    void    setVector3f(const GLchar* name, GLfloat x, GLfloat y, GLfloat z, GLboolean EquipShader = false);
    void    setVector3f(const GLchar* name, const vec3& value, GLboolean EquipShader = false);
    void    setVector4f(const GLchar* name, GLfloat x, GLfloat y, GLfloat z, GLfloat w, GLboolean EquipShader = false);
    void    setVector4f(const GLchar* name, const vec4& value, GLboolean EquipShader = false);
    void    setMatrix4(const GLchar* name, const mat4& matrix, GLboolean EquipShader = false);
    
    Shader& Equip();
private:
    string  shaderTypeStringFromEnum(SHADER_T type);
    void    checkErrorsInCompilation(GLuint object, SHADER_T type);
    void    equipShaderWhenSetting(GLboolean equipShader);
};