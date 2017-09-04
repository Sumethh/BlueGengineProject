#version 440 core

layout (location = 0) out vec3 gPosition;
layout (location = 1) out vec3 gNormal;
layout (location = 2) out vec4 gColorSpec;


in vec2 TexCoords;
in vec3 FragPos;
in vec3 Normal;

struct Material
{
    vec4 Diffuse;
    vec4 Ambient;
    float Specular;
};
uniform Material material;

uniform sampler2D textureDiffuse;
uniform float spec;
void main()
{
    gPosition = FragPos;
    gNormal = Normal;
    gColorSpec.rgb = texture(textureDiffuse, TexCoords).rgb;
    gColorSpec.a = spec;
}