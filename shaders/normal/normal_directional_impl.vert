// NORMAL_DIRECTIONAL_IMPL //

void Normal_setupDirectionalLights(mat3 tbnMatrix, int lightsCount)
{
    for (int i = 0; i < lightsCount; i++)
        var_directionalLightVectors[i] = tbnMatrix * directionalLights[i].direction;
}
