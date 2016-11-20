#version 330 core 

layout(location = 0) in vec3 position;

uniform mat4 view;
uniform mat4 projection;

uniform vec3 LightPos;

void main()
{
    mat4 model;
    model[0] = vec4(0.5,0,0,0);
    model[1] = vec4(0,0.5,0,0);
    model[2] = vec4(0,0,0.5,0);
    model[3] = vec4(LightPos,1);
    gl_Position = projection * view * model *vec4(position, 1.0f);
}