#version 330 core

out vec4 fragColor;
in vec2 texCoord;
in vec3 shade;
uniform sampler2D sprite;
uniform vec3 tint;

void main()
{
    vec4 text = texture(sprite,texCoord);
    fragColor = texture(sprite,texCoord);
}
