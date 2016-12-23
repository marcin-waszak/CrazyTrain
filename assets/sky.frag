#version 330 core

in vec3 FragPos;
in vec2 TexCoords;

out vec4 color;

uniform sampler2D material_diffuse;   // cannot be in struct

void main()
{
    color = vec4(vec3(texture(material_diffuse, TexCoords)), 1.0);
}
