// SHADOWS_DIRECTIONAL_IMPL //

void Shadows_setupDirectionalLights(vec4 WorldPos)
{
	for (int i = 0; i < maxDirectionalLights; ++i)
	{
		var_fragPosDirectionalLightSpace[i] = directionalLightSpaceMatrix[i] * WorldPos;
	}
}
