// COMBINE //

// Uniform variables
uniform sampler2D brightnessTexture;

vec4 Combine_getColor(vec4 inputColor)
{
	vec4 brightnessColor = texture(brightnessTexture, var_textureCoords);
	return inputColor + brightnessColor;
}
