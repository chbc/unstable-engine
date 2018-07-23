// POINT_LIGHTS_IMPL

void PointLights_compute(vec3 normal, vec3 toCameraDirection, inout vec3 kd, inout vec3 ks)
{
    float diffuseEnergy = 0;
    float specularEnergy = 0;
    for (int i = 0; i < MAX_POINT_LIGHTS; i++)
    {
        Lights_computeEnergies(normal, toCameraDirection, normalize(var_toPointLightVectors[i]), diffuseEnergy, specularEnergy);

        if ((diffuseEnergy > 0) && (length(var_toPointLightVectors[i]) < pointLights[i].range))
        {
            float shadow = 0;
            // [POINT_SHADOWS] shadow = Shadows_computePointLightShadow(i);

            diffuseEnergy *= (1 - shadow);
            specularEnergy *= (1 - shadow);

            float attenuation = PointLights_getAttenuation(i);

            vec3 lightColor = pointLights[i].color;

            kd += lightColor * diffuseEnergy * attenuation;
            ks += lightColor * specularEnergy * attenuation;
        }
    }
}

float PointLights_getAttenuation(int lightIndex)
{
    float result = 0.0f;

    float distance = length(var_toPointLightVectors[lightIndex]);
    result = 1 - (distance / pointLights[lightIndex].range);
    result *= pointLights[lightIndex].intensity;

    return result;
}
