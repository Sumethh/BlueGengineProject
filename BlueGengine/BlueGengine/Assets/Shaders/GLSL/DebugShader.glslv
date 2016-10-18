#version 410 core 

layout(location = 0) in vec3 location;
layout(location = 1) in vec4 color;

uniform mat4 view;
uniform mat4 projection;

out vec4 oColor;

void main()
{
    mat4 TranslationMat;
    TranslationMat[0] = vec4(1,0,0,0);
    TranslationMat[1] = vec4(0,1,0,0);
    TranslationMat[2] = vec4(0,0,1,0);
    TranslationMat[3] = vec4(location,1);
    gl_Position =  projection*view*TranslationMat*vec4(0.0f, 0.0f, 0.0f,1.0f);
    oColor = color;
}
