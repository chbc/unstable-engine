// MAIN_IMPL //

void main(void)
{
	/* ### GRAY SCALE
	vec4 color = texture(screenTexture, var_textureCoords);
	float avarage = 0.2126 * color.r + 0.7152 * color.g + 0.0722 * color.b;	
	out_color = vec4(avarage, avarage, avarage, 1.0);
	*/
	
	vec4 result = texture(screenTexture, var_textureCoords);
	// [INVERSE] result = Inverse_getColor(result);
	
	out_color = result;
}
