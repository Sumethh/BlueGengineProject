#version 330 core

in vec2 uv;
in vec3 oNormal;
in vec3 oFragPos;

out vec4 ocolor;

uniform vec3 viewPos;

uniform sampler2D baseTexture;

struct PointLight
{
    vec3 position;
     
    float constant;
    float linear;
    float quadratic;

    vec3 color;
};
uniform PointLight pl;

struct DirectionalLight
{
    vec3 direction;
    vec3 color;
};
uniform DirectionalLight dl;

struct SpotLight {
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
    vec3 diffuse = diff * light.color * vec3(material.Diffuse);

    vec3 reflectDir = reflect(-lightDir,normal);
    float spec = pow(max(dot(viewDir,reflectDir),0.0f),32);
    vec3 specular = vec3(1.0f, 1.0f, 1.0f) * spec * material.Specular * light.color;

    float distance = length(light.position - fragPos);
    float attenuation = 1.0f / (light.constant + light.linear * distance + light.quadratic * (distance * distance));

    diffuse *= attenuation;
    specular *= attenuation;
    vec3 result = diffuse + specular;
    return result;
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
    vec3 diffuse = light.color * diff * vec3(material.Diffuse);
     vec3 specular = vec3(1.0f, 1.0f, 1.0f) * spec * material.Specular * light.color;
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
    //Ambient
    //Make the ambient power part of the world rather than a constant?
    vec3 ambient = 1.0f * vec3(material.Ambient);
    vec3 norm = normalize(oNormal);
    vec3 viewDir = normalize(viewPos - oFragPos);
    vec3 result = CalcPointLight(pl, norm, oFragPos,viewDir);    
    result += CalcDirLight(dl, norm, viewDir);
    result += ambient;
    ocolor = vec4(result, 1.0f) * texture(baseTexture, uv);
}