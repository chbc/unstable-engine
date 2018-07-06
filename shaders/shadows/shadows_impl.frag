// SHADOWS_IMPL
vec3 sampleOffsetDirections[5] = vec3[]
(
    vec3(1, 1, 1),  /*vec3(1, -1, 1),     vec3(-1, -1, 1),    /*vec3(-1, 1, 1), */
    vec3(1, 1, -1), /*vec3(1, -1, -1),    vec3(-1, -1, -1),   /*vec3(-1, 1, -1),*/
    vec3(1, 1, 0),  /*vec3(1, -1, 0),     vec3(-1, -1, 0),    /*vec3(-1, 1, 0), */
    vec3(1, 0, 1),  /*vec3(-1, 0, 1),     vec3(1, 0, -1),     /*vec3(-1, 0, -1),*/
    vec3(0, 1, 1)  /*vec3(0, -1, 1),     vec3(0, -1, -1)    /*vec3(0, 1, -1)  */
);

float Shadows_computePointLightShadow(int lightIndex)
{
    float result = 0.0;

    vec3 toFragmentVector = var_lightToFragmentVectors[lightIndex];
    float currentDepth = length(toFragmentVector);

    float bias = 0.15;
    int samples = 5;

    float farPlane = lights.pointLights[lightIndex].range;
    float viewDistance = length(var_toCameraVector);
    float diskRadius = (1.0 + (viewDistance / farPlane)) / farPlane;

    float closestDepth;
    for (int i = 0; i < samples; ++i)
    {
        // ### closestDepth = texture(pointShadowMaps[lightIndex], toFragmentVector + sampleOffsetDirections[i] * diskRadius).r;
        closestDepth *= farPlane;
        if (currentDepth - bias > closestDepth)
            result += 1.0;
    }

    result /= float(samples);

    /* ###
    float closestDepth = texture(shadowMaps[XXX_lightIndex], toFragmentVector).r * farPlane;
    if (currentDepth - bias > closestDepth)
    result = 1.0;
    */

    return result;
}

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
