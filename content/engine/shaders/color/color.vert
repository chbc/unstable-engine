#version 420

layout(location = 0) in vec3 in_position;

layout (std140, binding = 1) uniform CameraBuffer
{
	mat4 projectionMatrix;
	mat4 viewMatrix;
};

uniform mat4 modelMatrix;

void main()
{
	vec4 vertexPosition = modelMatrix * vec4(in_position, 1.0);
	gl_Position = projectionMatrix * viewMatrix * vertexPosition;
}
