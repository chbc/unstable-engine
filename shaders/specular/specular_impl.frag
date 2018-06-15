// SPECULAR_IMPL //

void Specular_computeSpecular(inout vec3 ks)
{
	ks = ks * texture(specularTexture, var_textureCoords).rgb;
}
