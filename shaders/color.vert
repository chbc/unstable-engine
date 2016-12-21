#version 400

layout(location=0) in vec3 in_position;
layout(location=1) in vec3 in_normal;

uniform mat4 MVP;
uniform vec4 materialColor;

out vec4 var_position;
out vec3 var_normal;
out vec4 var_materialColor;
out vec3 var_lightDirection;


void main(void)
{
	var_materialColor = materialColor;
	var_normal = (MVP * vec4(in_normal, 0.0)).xyz;
	var_lightDirection = vec3(1.0, -1.0, 1.0);
	
	var_position = MVP * vec4(in_position, 1.0);
	gl_Position = var_position;
}
