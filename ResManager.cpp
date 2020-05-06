#include "res_manager_h.h"

#include <iostream>
#include <sstream>
#include <fstream>

#include <SOIL2.h>
using namespace std;

// Instantiate static variables
map<string, Texture>    ResManager::textures;
map<string, Shader>       ResManager::shaders;


void ResManager::UnloadTexture(string name)
{
    try {
        if(textures.find(name)!=textures.end())
            glDeleteTextures(1, &textures[name].Id);
    }
    catch (exception e) {
        cerr << "Exception while unloading texture : " << e.what();
    }
}

Shader ResManager::LoadShader(const GLchar* vertexShaderFile, const GLchar* fragmentShaderFile, string name)
{
    shaders[name] = loadShaderFromFile(vertexShaderFile, fragmentShaderFile);
    return shaders[name];
}

Shader ResManager::GetShader(string name)
{
    return shaders[name];
}

Texture ResManager::LoadTexture(const GLchar* file, GLboolean alpha, string name)
{
    textures[name] = loadTextureFromFile(file, alpha);
    return textures[name];
}

Texture ResManager::GetTexture(string name)
{
    return textures[name];
}

void ResManager::CleanUp()
{
    //deleting all shaders	
    for (auto shader : shaders)
        glDeleteProgram(shader.second.shaderId);


    //deleting all textures
    for (auto texture : textures)
        glDeleteTextures(1, &texture.second.Id);
}

Shader ResManager::loadShaderFromFile(const GLchar* vertexShaderFile, const GLchar* fragmentShaderFile)
{
    //Fetching the source from the file path(s)
   string vertexCode;
   string fragmentCode;
   string geometryCode;
    try
    {
        // Open the files
        ifstream vertexShaderFile(vertexShaderFile);
        ifstream fragmentShaderFile(fragmentShaderFile);
        
        stringstream vShaderStream, fShaderStream;
        
        // Read the file's buffer contents into their respective streams
        vShaderStream << vertexShaderFile.rdbuf();
        fShaderStream << fragmentShaderFile.rdbuf();
        
        // closing the file handlers
        vertexShaderFile.close();
        fragmentShaderFile.close();
        
        // Converting the streams into their respective string
        vertexCode = vShaderStream.str();
        fragmentCode = fShaderStream.str();
       
    }
    catch (exception e)
    {
        cerr << "error on reading shader files" << endl;
    }
    const GLchar* vShaderCode = vertexCode.c_str();
    const GLchar* fShaderCode = fragmentCode.c_str();
    const GLchar* gShaderCode = geometryCode.c_str();
    
    // Using the source to create shader objects
    Shader shader;
    shader.Build(vShaderCode, fShaderCode);
    return shader;
}

Texture ResManager::loadTextureFromFile(const GLchar* file, GLboolean alpha)
{
    Texture texture;

    //If alpha is provided then opening up that channel
    if (alpha)
    {
        texture.internalFormat = GL_RGBA;
        texture.imageFormat = GL_RGBA;
    }

    // Loading the image
    int width, height;
    unsigned char* image_data = SOIL_load_image(file, &width, &height, 0, texture.imageFormat == GL_RGBA ? SOIL_LOAD_RGBA : SOIL_LOAD_RGB);
    // Generating texture
    texture.genTexture(width, height, image_data);
    
    //Now that I have the texture, I'm going to free the image data
    SOIL_free_image_data(image_data);
    return texture;
}