#version 400

uniform vec4 materialColor;

// Out variables
layout (location = 0) out vec4 out_color;

void main(void)
{
	out_color = materialColor;
}
