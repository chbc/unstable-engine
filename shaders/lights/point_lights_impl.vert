// LIGHTS_IMPL //

void PointLights_setup(vec3 vertexPosition)
{
    // Point lights
    for (int i = 0; i < MAX_POINT_LIGHTS; i++)
    {
        var_toPointLightVectors[i] = lights.pointLights[i].position - vertexPosition;
        // [SHADOWS] Shadows_setLightToFragmentVector(vertexPosition - pointLights[i].position, i);
    }
}
