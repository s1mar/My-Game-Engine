#version 330 core
in vec2 textureCoordinates;
out vec4 color;

uniform sampler2D texImage;
uniform vec3 spriteColor;

void main()
{    
    color = vec4(spriteColor, 1.0) * texture(texImage, textureCoordinates);
   
}  