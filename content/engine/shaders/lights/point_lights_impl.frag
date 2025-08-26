// POINT_LIGHTS_IMPL

void PointLights_compute(vec3 normal, vec3 toCameraDirection, inout vec3 kd, inout vec3 ks)
{
    float diffuseEnergy = 0;
    float specularEnergy = 0;
    for (int i = 0; i < maxPointLights; i++)
    {
		vec3 lightVector = var_worldPosition - vec3(pointLights[i].position);
		// [NORMAL] Normal_getLightVector(lightVector);
		vec3 toPointLightVector = -lightVector;
        Lights_computeEnergies(normal, toCameraDirection, normalize(toPointLightVector), diffuseEnergy, specularEnergy);

		float range = pointLights[i].rangeAndIntensity.x;
        if ((diffuseEnergy > 0) && (length(toPointLightVector) < range))
        {
            float shadow = 0;
            // [POINT_SHADOWS] shadow = Shadows_computePointLightShadow(i);

            diffuseEnergy *= (1 - shadow);
            specularEnergy *= (1 - shadow);

            float attenuation = PointLights_getAttenuation(i, toPointLightVector);

            vec3 lightColor = vec3(pointLights[i].color);

            kd += lightColor * diffuseEnergy * attenuation;
            ks += lightColor * specularEnergy * attenuation;
        }
    }
}

float PointLights_getAttenuation(int lightIndex, vec3 toPointLightVector)
{
    float result = 0.0f;

    float distance = length(toPointLightVector);
	float range = pointLights[lightIndex].rangeAndIntensity.x;
	float intensity = pointLights[lightIndex].rangeAndIntensity.y;
    result = 1 - (distance / range);
    result *= intensity;

    return result;
}
