// SHADOWS_DIRECTIONAL_IMPL

float Shadows_computeDirectionalLightShadow(vec3 normal, vec3 toLightDirection, int lightIndex)
{
    float result = 0.0;

    vec3 projCoords = var_fragPosDirectionalLightSpace[lightIndex].xyz / var_fragPosDirectionalLightSpace[lightIndex].w;
    projCoords = (projCoords * 0.5) + 0.5;

    float closestDepth = texture(directionalShadowMaps[lightIndex], projCoords.xy).r;
    float currentDepth = projCoords.z;

    if (currentDepth < 1.0)
    {
        float bias = max(0.05 * (1.0 - dot(normal, toLightDirection)), 0.005);

        vec2 texelSize = 1.0 / textureSize(directionalShadowMaps[lightIndex], 0);
        for (int x = -1; x <= 1; ++x)
        {
            for (int y = -1; y <= 1; ++y)
            {
                float pcfDepth = texture(directionalShadowMaps[lightIndex], projCoords.xy + vec2(x, y) * texelSize).r;
                result += (currentDepth - bias) > pcfDepth ? 1.0 : 0.0;
            }
        }

        result /= 9.0;
    }

    return result;
}
