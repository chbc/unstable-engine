#version 420

layout(location = 0) in vec3 in_position;

// Matrices
uniform mat4 modelMatrix;

// Camera UBO
layout (std140, binding = 1) uniform CameraBuffer
{
	mat4 projectionMatrix;
	mat4 viewMatrix;
};

void main()
{
	vec4 vertexPosition = modelMatrix * vec4(in_position, 1.0);
	gl_Position = projectionMatrix * viewMatrix * vertexPosition;
}
