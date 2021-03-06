#version 440 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec2 uvs;
layout(location = 2) in vec3 normal;

out vec2 TexCoords;
out vec3 FragPos;
out vec3 Normal;

uniform sampler2D textureDiffuse;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

void main()
{
    gl_Position = projection * view * model *vec4(position, 1.0f);
    TexCoords = uvs;
    Normal = mat3(transpose(inverse(model))) *normal;
    FragPos = vec3(model*vec4(position,1.0f));
}