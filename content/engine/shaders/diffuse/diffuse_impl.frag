// DIFFUSE_IMPL //

vec4 Diffuse_computeTextureColor(vec3 ka, vec3 kd, vec3 ks)
{
	vec4 kt = texture2D(diffuseTexture, var_textureCoords);
	vec3 resultColor = (ka * kt.rgb) + (kd * kt.rgb) + (ks * kt.rgb);
	
	return vec4(resultColor, kt.a);
}
