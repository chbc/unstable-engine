#version 400

uniform sampler2D screenTexture;

in vec2 var_textureCoords;

out vec4 out_color;

void main(void)
{
	/* ### GRAY SCALE
	vec4 color = texture(screenTexture, var_textureCoords);
	float avarage = 0.2126 * color.r + 0.7152 * color.g + 0.0722 * color.b;	
	out_color = vec4(avarage, avarage, avarage, 1.0);
	*/
	out_color = vec4(1.0 - texture(screenTexture, var_textureCoords));
}
