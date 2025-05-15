// LIGHTS_IMPL

vec3 Lights_computeAmbientLight(vec3 materialColor)
{
    return ambientLightColor * materialColor;
}

void Lights_computeDiffuseAndSpecularLights(vec3 normal, inout vec3 kd, inout vec3 ks)
{
    vec3 toCameraDirection = normalize(cameraPosition - var_worldPosition);

    // [DIRECTIONAL_LIGHTS] DirectionalLights_compute(normal, toCameraDirection, kd, ks);
    // [POINT_LIGHTS] PointLights_compute(normal, toCameraDirection, kd, ks);
}

void Lights_computeEnergies(vec3 normal, vec3 toCameraDirection, vec3 toLightDirection, inout float diffuseEnergy, inout float specularEnergy)
{
    vec3 halfVector = normalize(toLightDirection + toCameraDirection);

    diffuseEnergy = max(dot(normal, toLightDirection), 0.0);
    specularEnergy = max(dot(normal, halfVector), 0.0);

    if (specularEnergy > 0.0)
        specularEnergy = pow(specularEnergy, shininess);
}
