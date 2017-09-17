#version 440 core

in vec2 texCoords;

layout(binding = 0) uniform sampler2D gPosition;
layout(binding = 1) uniform sampler2D gNormal;
layout(binding = 2) uniform sampler2D gColorSpec;

const int MAX_LIGHTS = 64; 

out vec4 outColor;
uniform vec3 viewPos;

float constant = 1;
float linear = 0.7;
float quadratic = 1.8;
struct PointLight
{
    vec3 position;
    vec3 color;   
};
uniform int pointLightCount = 1;
uniform PointLight pointLights[MAX_LIGHTS];

struct DirectionalLight
{
    vec3 direction;
    vec3 color;
};
uniform int directionalLightCount = 1;
uniform DirectionalLight directionalLights[MAX_LIGHTS];

struct SpotLight 
{
    vec3 position;
    vec3 direction;
    float cutOff;
    float outerCutOff;
  
    float constant;
    float linear;
    float quadratic;

    vec3 color;    
};

struct Material
{
    vec4 Diffuse;
    vec4 Ambient;
    float Specular;
};
uniform Material material;


vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir)
{
    vec3 lightDir = normalize(light.position - fragPos);
    float diff = max(dot(normal,lightDir),0.0f);
    vec3 diffuse = diff * light.color;

    vec3 reflectDir = reflect(-lightDir,normal);
    float spec = pow(max(dot(viewDir,reflectDir),0.0f),32);
    vec3 specular = vec3(1.0f, 1.0f, 1.0f) * spec * light.color;

    float distance = length(light.position - fragPos);
    float attenuation = 1.0f / (constant + linear * distance +quadratic * (distance * distance));

    diffuse *= attenuation;
    specular *= attenuation;
    return( diffuse + specular );
    
}

vec3 CalcDirLight(DirectionalLight light, vec3 normal, vec3 viewDir)
{
    vec3 lightDir = normalize(-light.direction);
    // Diffuse shading
    float diff = max(dot(normal, lightDir), 0.0);
    // Specular shading
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    // Combine results
    vec3 diffuse = light.color * diff;
    vec3 specular = vec3(1.0f, 1.0f, 1.0f) * spec * light.color;
    return (diffuse + specular);
}

vec3 CalcSpotLight(SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDir)
{
    vec3 lightDir = normalize(light.position - fragPos);
    // Diffuse shading
    float diff = max(dot(normal, lightDir), 0.0);
    // Specular shading
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.Specular);
    // Attenuation
    float distance = length(light.position - fragPos);
    float attenuation = 1.0f / (light.constant + light.linear * distance + light.quadratic * (distance * distance));    
    // Spotlight intensity
    float theta = dot(lightDir, normalize(-light.direction)); 
    float epsilon = light.cutOff - light.outerCutOff;
    float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0, 1.0);
    // Combine results
    vec3 ambient = light.color * vec3(material.Diffuse);
    vec3 diffuse = light.color * diff * vec3(material.Diffuse);
    vec3 specular = light.color * spec;
    ambient *= attenuation * intensity;
    diffuse *= attenuation * intensity;
    specular *= attenuation * intensity;
    return (ambient + diffuse + specular);
}

void main()
{
    vec3 fragPos = texture(gPosition, texCoords).rgb;
    vec3 normal = texture(gNormal, texCoords).rgb;
    vec3 color = texture(gColorSpec, texCoords).rgb;
    float spec = texture(gColorSpec, texCoords).a;

    vec3 lighting = color * 0.15f; //hardcoded ambient
    vec3 viewDir = normalize(viewPos - fragPos);

    for(int i=0; i < directionalLightCount; ++i)
    {
        vec3 lightDir = normalize(-directionalLights[i].direction);
        float diff = max(dot(normal, lightDir),0.0);
        lighting += diff * color * directionalLights[i].color;
        //lighting += CalcDirLight(directionalLights[i], normal, viewDir);
    }
    for(int i=0; i < pointLightCount; ++i)
    {
        vec3 lightDir = normalize(pointLights[i].position - fragPos);
        vec3 diffuse = max(dot(normal, lightDir), 0.0) * color * pointLights[i].color;
        lighting += diffuse;
        //lighting += CalcPointLight(pointLights[i], normal, fragPos, viewDir);
    }

    outColor = vec4(lighting,1);
}