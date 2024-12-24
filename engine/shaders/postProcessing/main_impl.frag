// MAIN_IMPL //

void main(void)
{
	vec4 result = texture(screenTexture, var_textureCoords);
	// [INCLUDE]
	
	out_color = result;
}
