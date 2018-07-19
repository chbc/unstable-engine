// DIRECTIONAL_LIGHTS_IMPL //

void DirectionalLights_setup(vec3 vertexPosition)
{
    // Directional lights
    for (int i = 0; i < MAX_DIRECTIONAL_LIGHTS; i++)
    {
        var_directionalLightVectors[i] = directionalLights[i].direction;
        // [SHADOWS] Shadows_setFragPosDirectionalLightSpace(vertexPosition, i);
    }
}
