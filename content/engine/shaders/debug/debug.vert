#version 400

layout(location = 0) in vec3 in_position;

// Matrices
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

void main()
{
	vec4 vertexPosition = vec4(in_position, 1.0);
	gl_Position = projectionMatrix * viewMatrix * vertexPosition;
}
