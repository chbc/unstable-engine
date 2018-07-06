// LIGHTS_IMPL

// Functions
vec3 Lights_computeAmbientLight(vec3 materialColor)
{
    return lights.ambientLightColor * materialColor;
}

void Lights_computeDiffuseAndSpecularLights(inout vec3 kd, inout vec3 ks)
{
    vec3 normal = normalize(var_normal);
    vec3 toCameraDirection = normalize(var_toCameraVector);

    // [NORMAL] normal = Normal_computeNormal();
    Lights_computeDirectionalLights(normal, toCameraDirection, kd, ks);
    Lights_computePointLights(normal, toCameraDirection, kd, ks);
}

void Lights_computeDirectionalLights(vec3 normal, vec3 toCameraDirection, inout vec3 kd, inout vec3 ks)
{
    float diffuseEnergy = 0.0;
    float specularEnergy = 0.0;

    for (int i = 0; i < lights.directionalLightsCount; i++)
    {
        vec3 lightColor = lights.directionalLights[i].color;
        vec3 toLightDirection = normalize(-var_directionalLightVectors[i]);

        Lights_computeEnergies(normal, toCameraDirection, toLightDirection, diffuseEnergy, specularEnergy);

        float shadow = 0;
        // [SHADOWS] shadow = Shadows_computeDirectionalLightShadow(normal, toLightDirection, i);

        diffuseEnergy *= (1 - shadow);
        specularEnergy *= (1 - shadow);

        kd = kd + (lightColor * diffuseEnergy);
        ks = ks + (lightColor * specularEnergy);
    }
}

void Lights_computePointLights(vec3 normal, vec3 toCameraDirection, inout vec3 kd, inout vec3 ks)
{
    float diffuseEnergy = 0;
    float specularEnergy = 0;
    for (int i = 0; i < lights.pointLightsCount; i++)
    {
        Lights_computeEnergies(normal, toCameraDirection, normalize(var_toPointLightVectors[i]), diffuseEnergy, specularEnergy);

        if ((diffuseEnergy > 0) && (length(var_toPointLightVectors[i]) < lights.pointLights[i].range))
        {
            float shadow = 0;
            // [SHADOWS] shadow = Shadows_computePointLightShadow(i);

            diffuseEnergy *= (1 - shadow);
            specularEnergy *= (1 - shadow);

            float attenuation = Lights_getAttenuation(i);

            vec3 lightColor = lights.pointLights[i].color;

            kd += lightColor * diffuseEnergy * attenuation;
            ks += lightColor * specularEnergy * attenuation;
        }
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

float Lights_getAttenuation(int lightIndex)
{
    float result = 0.0f;

    float distance = length(var_toPointLightVectors[lightIndex]);
    result = 1 - (distance / lights.pointLights[lightIndex].range);
    result *= lights.pointLights[lightIndex].intensity;

    return result;
}
