#version 330

layout(location = 0) in vec3 in_position;

// Matrices
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;
uniform mat4 modelMatrix;

out vec3 worldPosition;

void main()
{
	vec4 vertexPosition = modelMatrix * vec4(in_position, 1.0);
	worldPosition = vertexPosition.xyz;
	gl_Position = projectionMatrix * viewMatrix * vertexPosition;
}
