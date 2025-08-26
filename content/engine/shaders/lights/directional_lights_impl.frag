// DIRECTIONAL_LIGHTS_IMPL

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
