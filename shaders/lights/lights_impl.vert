// LIGHTS_IMPL //

void Lights_setup(vec3 vertexPosition)
{
    // Point lights
    for (int i = 0; i < lights.pointLightsCount; i++)
        var_toPointLightVectors[i] = lights.pointLights[i].position - vertexPosition;
    
    // Directional lights
    for (int i = 0; i < lights.directionalLightsCount; i++)
        var_directionalLightVectors[i] = lights.directionalLights[i].direction;
}
