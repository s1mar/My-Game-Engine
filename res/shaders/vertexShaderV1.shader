#version 330 core
layout (location = 0) in vec4 vertex; //wrapping 2d pos and texture coordinates in one vec4

out vec2 textureCoordinates;

uniform mat4 model;
uniform mat4 projection;

void main()
{
    textureCoordinates = vertex.zw;
    gl_Position = projection * model * vec4(vertex.xy, 0.0, 1.0);
}