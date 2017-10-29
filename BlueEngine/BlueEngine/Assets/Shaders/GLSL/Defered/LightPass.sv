#version 440 core
layout (location = 0) in vec3 inPosition;
layout (location  = 1) in vec2 inTexCoords;

out vec2 texCoords;
uniform mat4 projection;
void main()
{
    gl_Position = vec4(inPosition,1);
    texCoords = inTexCoords;
}