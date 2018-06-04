#version 330 core

layout(location = 0) in vec3 in_position;

uniform mat4 sourceSpaceMatrix;
uniform mat4 modelMatrix;

out vec2 var_textureCoords;

void main()
{
    gl_Position = sourceSpaceMatrix * modelMatrix * vec4(in_position, 1.0);
}
