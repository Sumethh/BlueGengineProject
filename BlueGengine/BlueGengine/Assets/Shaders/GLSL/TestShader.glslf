#version 440 core 

out vec4 color;
in vec2 uv;
uniform sampler2D baseTexture;

void main()
{
    color = texture(baseTexture, uv);
    //color = vec4(1.0f, 0.0f, 0.0f, 1.0f);
}
