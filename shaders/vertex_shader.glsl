#version 330 core
layout (location = 0) in vec3 pos;
layout (location = 1) in vec3 color;

uniform mat4 matrix;

out vec3 vertexColor;

void main()
{
    vertexColor = color;
    gl_Position = vec4(pos.x, pos.y, pos.z, 1.0) * matrix;
}