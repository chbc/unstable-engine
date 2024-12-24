// SPECULAR_IMPL //

void AmbientOclusion_computeAO(inout vec3 ka)
{
	ka = ka * texture(aoTexture, var_textureCoords).rgb;
}
