#version 400

uniform sampler2D guiTexture;

in vec2 var_textureCoords;

out vec4 out_color;

void main(void)
{
	out_color = texture(guiTexture, var_textureCoords);
}
