#version 330 core

layout (location = 0) in vec3 in_position;

uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

out vec3 WorldPos;

void main()
{
    WorldPos = in_position;  
    gl_Position =  projectionMatrix * viewMatrix * in_position;
}
