#version 330 core
in vec3 vertexColor;

out vec4 FragColor;

uniform vec2 res;

void main()
{
    FragColor = vec4(vertexColor, 1.0);
}