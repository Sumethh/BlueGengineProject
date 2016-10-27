#version 330 core 


layout(location = 0) in vec3 position;
layout(location = 1) in vec2 uvs;
layout(location = 2) in vec3 normal;
layout(location = 5) in vec3 modelPos;

out vec2 uv;
out vec3 oNormal;
out vec3 oFragPos;
out vec3 viewDir;

uniform mat4 view;
uniform mat4 projection;
uniform mat4 model;
void main()
{    
    gl_Position = projection * view * model *vec4(position, 1.0f);
    uv = uvs;
    oNormal = mat3(transpose(inverse(model))) *normal;
    viewDir = vec3(0,0,0) - (view * model * vec4(position, 1.0f)).xyz;
    oFragPos = vec3(model*vec4(position,1.0f));
}