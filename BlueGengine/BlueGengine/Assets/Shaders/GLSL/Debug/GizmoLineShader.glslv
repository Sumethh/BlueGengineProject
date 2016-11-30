#version 440 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec4 inColor; 

out vec4 color;
uniform mat4 projection;
uniform mat4 view;

void main()
{
    gl_Position = projection * view * vec4(position, 1.0f);
    color = inColor;
}