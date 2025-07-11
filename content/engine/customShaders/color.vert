#version 400

layout(location = 0) in vec3 in_position;

// Matrices
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;
uniform mat4 modelMatrix;

void main()
{
	vec4 vertexPosition = modelMatrix * vec4(in_position, 1.0);
	gl_Position = projectionMatrix * viewMatrix * vertexPosition;
}
