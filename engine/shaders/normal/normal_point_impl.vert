// NORMAL_POINT_IMPL //

void Normal_setupPointLights(mat3 tbnMatrix, int lightsCount)
{
    for (int i = 0; i < lightsCount; i++)
        var_toPointLightVectors[i] = tbnMatrix * var_toPointLightVectors[i];
}
