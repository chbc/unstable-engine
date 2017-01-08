#version 400

// Vertices
layout(location=0) in vec3 in_position;
layout(location=1) in vec3 in_normal;

// Matrices
uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

// Varying variables
out vec4 var_position;
out vec3 var_normal;

void main(void)
{
	vec4 var_position = modelMatrix * vec4(in_position, 1.0);
	var_normal = (modelMatrix * vec4(in_normal, 0)).xyz;

	gl_Position = projectionMatrix * viewMatrix * var_position;
}
