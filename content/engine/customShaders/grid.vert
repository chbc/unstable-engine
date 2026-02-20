#version 420

layout(location = 0) in vec3 in_position;

layout (std140, binding = 1) uniform CameraBuffer
{
	mat4 projectionMatrix;
	mat4 viewMatrix;
};

// Matrices
uniform mat4 modelMatrix;

out vec3 worldPosition;

void main()
{
	vec4 vertexPosition = modelMatrix * vec4(in_position, 1.0);
	worldPosition = vertexPosition.xyz;
	gl_Position = projectionMatrix * viewMatrix * vertexPosition;
}
