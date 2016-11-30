#version 440 core

in vec4 color;
out vec4 oColor;
void main()
{
    oColor = color;
    //oColor = vec4(1.0f,1.0f,1.0f,1.0f);
}