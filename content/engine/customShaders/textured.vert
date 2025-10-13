#version 400

layout (location = 0) in vec3 in_position;
layout (location = 2) in vec2 in_textureCoords;

// Matrices
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;
uniform mat4 modelMatrix;

out vec2 var_texCoords;

void main()
{
	var_texCoords = in_textureCoords;
	vec4 vertexPosition = modelMatrix * vec4(in_position, 1.0);
	gl_Position = projectionMatrix * viewMatrix * vertexPosition;
}
