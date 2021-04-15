// GRAYSCALE //

vec4 Grayscale_getColor(vec4 inputColor)
{
	float avarage = 0.2126 * inputColor.r + 0.7152 * inputColor.g + 0.0722 * inputColor.b;	
	return vec4(avarage, avarage, avarage, 1.0);
}
