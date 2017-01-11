#version 440 core

uniform vec4 objectColor;
out vec4 oColor;

in vec3 viewPos;
in vec3 oNormal;
in vec3 dirToCamera;
void main()
{
    oColor = objectColor;
}