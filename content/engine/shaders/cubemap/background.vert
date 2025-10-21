#version 330 core
layout (location = 0) in vec3 in_position;

uniform mat4 projectionMatrix;
uniform mat4 viewMatrix;

out vec3 WorldPos;

void main()
{
    WorldPos = in_position;

	mat4 rotView = mat4(mat3(viewMatrix));
	vec4 clipPos = projectionMatrix * rotView * vec4(WorldPos, 1.0);

	gl_Position = clipPos.xyww;
}
