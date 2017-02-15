// NORMAL_IMPL //

vec4 Normal_computeNormal(vec3 ka, vec3 kd, vec3 ks)
{
	vec3 kt = texture(normalTexture, var_textureCoords).rgb;
	vec3 resultColor = (ka * kt) + (kd * kt) + ks;
	
	return vec4(resultColor, 1.0);
}
