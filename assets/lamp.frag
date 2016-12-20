#version 330 core
out vec4 color;

uniform vec3 LightColor;

void main()
{
    color = vec4(LightColor, 1.0f); // Set alle 4 vector values to 1.0f
}
