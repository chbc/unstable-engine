// LIGHTS_IMPL

vec3 Lights_computeAmbientLight(vec3 materialColor)
{
    return ambientLightColor * materialColor;
}

void Lights_computeDiffuseAndSpecularLights(vec3 normal, inout vec3 kd, inout vec3 ks)
{
    vec3 toCameraDirection = normalize(cameraPosition - var_worldPosition);

	if (maxDirectionalLights > 0)
	{
		DirectionalLights_compute(normal, toCameraDirection, kd, ks);
	}
    
	if (maxPointLights > 0)
	{
		PointLights_compute(normal, toCameraDirection, kd, ks);
	}
}

void Lights_computeEnergies(vec3 normal, vec3 toCameraDirection, vec3 toLightDirection, inout float diffuseEnergy, inout float specularEnergy)
{
    vec3 halfVector = normalize(toLightDirection + toCameraDirection);

    diffuseEnergy = max(dot(normal, toLightDirection), 0.0);
    specularEnergy = max(dot(normal, halfVector), 0.0);

    if (specularEnergy > 0.0)
        specularEnergy = pow(specularEnergy, shininess);
}

void DirectionalLights_compute(vec3 normal, vec3 toCameraDirection, inout vec3 kd, inout vec3 ks)
{
    float diffuseEnergy = 0.0;
    float specularEnergy = 0.0;

    for (int i = 0; i < maxDirectionalLights; i++)
    {
        vec3 lightColor = vec3(directionalLights[i].color);
		vec3 lightVector = vec3(directionalLights[i].direction);
		
		// [NORMAL] Normal_getLightVector(lightVector);
        vec3 toLightDirection = normalize(-lightVector);

        Lights_computeEnergies(normal, toCameraDirection, toLightDirection, diffuseEnergy, specularEnergy);

        float shadow = 0;
        // [DIRECTIONAL_SHADOWS] shadow = Shadows_computeDirectionalLightShadow(normal, toLightDirection, i);

        diffuseEnergy *= (1 - shadow);
        specularEnergy *= (1 - shadow);

        kd = kd + (lightColor * diffuseEnergy);
        ks = ks + (lightColor * specularEnergy);
    }
}

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
