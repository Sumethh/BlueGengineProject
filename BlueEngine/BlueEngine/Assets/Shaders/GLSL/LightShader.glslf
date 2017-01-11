#version 330 core

out vec4 ocolor;

uniform vec3 LightColor;

void main()
{
    ocolor = vec4(LightColor,1.0f);
}