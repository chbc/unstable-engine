#version 400

layout (location = 0) out vec4 out_color;

uniform sampler2D textureMap;

in vec2 var_texCoords;

void main(void)
{
	out_color = texture(textureMap, var_texCoords);
}
