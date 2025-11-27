// SHADOWS_POINT_IMPL //

void Shadows_setupPointLights(vec4 WorldPos)
{
	for (int i = 0; i < maxPointLights; ++i)
	{
		var_lightToFragmentVectors[i] = (WorldPos - pointLights[i].position).xyz;
	}
}
