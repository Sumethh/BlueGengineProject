#version 440 core

uniform vec4 objectColor;

out vec4 oColor;
void main()
{
    oColor = objectColor;
}