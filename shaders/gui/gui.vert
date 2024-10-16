#version 400

layout(location = 0) in vec2 in_position;
layout(location = 2) in vec2 in_textureCoords;

uniform mat4 modelMatrix;

out vec2 var_textureCoords;

void main()
{
	var_textureCoords = in_textureCoords;
	gl_Position = modelMatrix * vec4(in_position, 0.0, 1.0);
}
