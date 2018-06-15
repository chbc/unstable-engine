// NORMAL_IMPL //

vec3 Normal_computeNormal()
{
	vec3 result = texture(normalTexture, var_textureCoords).rgb;
	result = normalize((result * 2.0) - 1.0);
	
	return result;
}
