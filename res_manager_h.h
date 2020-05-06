#pragma once
/** 
The Resources manager, as a utility module in my engine.
This static-singleton class handles the heavy lifting for tasks like loading textures and shaders. Each loaded item is also stored for future
reference by string identifiers.
**/

#include <map>
#include <string>

#include <glew.h>

#include "texture_h.h"
#include "shader_h.h"

using namespace std;

class ResManager
{
public:
    // Storing the shaders and textures
    static map<string, Shader>    shaders;
    static map<string, Texture> textures;

    // Loading the shaders
    static Shader LoadShader(const GLchar* vertexShaderFile, const GLchar* fragmentShaderFile,string name);
    
    // Retrieving a stored shader
    static Shader  GetShader(string name);
    
    // Loading a texture from file
    static Texture LoadTexture(const GLchar* file, GLboolean alpha,string name);
    
    static void UnloadTexture(string name);

    // Retrieving a stored texture
    static Texture GetTexture(string name);
    
    // clean-up of all loaded resources
    static void  CleanUp();
private:
    
    ResManager() { }
    
    // Loading and generating a shader from file
    static Shader  loadShaderFromFile(const GLchar* vertexShaderFile, const GLchar* fragmentShaderFile);
    // Loading and generating a single texture from file
    static Texture loadTextureFromFile(const GLchar* file, GLboolean alpha);
};
