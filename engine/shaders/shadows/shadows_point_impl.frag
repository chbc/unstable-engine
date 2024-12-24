// SHADOWS_POINT_IMPL

vec3 sampleOffsetDirections[5] = vec3[]
(
    vec3(1, 1, 1),  /*vec3(1, -1, 1),     vec3(-1, -1, 1),    vec3(-1, 1, 1) */ 
    vec3(1, 1, -1), /*vec3(1, -1, -1),    vec3(-1, -1, -1),   vec3(-1, 1, -1)*/
    vec3(1, 1, 0),  /*vec3(1, -1, 0),     vec3(-1, -1, 0),    vec3(-1, 1, 0) */ 
    vec3(1, 0, 1),  /*vec3(-1, 0, 1),     vec3(1, 0, -1),     vec3(-1, 0, -1)*/
    vec3(0, 1, 1)   /*vec3(0, -1, 1),     vec3(0, -1, -1)     vec3(0, 1, -1) */ 
);

float Shadows_computePointLightShadow(int lightIndex)
{
    float result = 0.0;

    vec3 toFragmentVector = var_lightToFragmentVectors[lightIndex];
    float currentDepth = length(toFragmentVector);

    float bias = 0.15;
    int samples = 5;

    float farPlane = pointLights[lightIndex].range;

    /* ###
    float viewDistance = length(var_toCameraVector);
    float diskRadius = (1.0 + (viewDistance / farPlane)) / farPlane;

    float closestDepth;
    for (int i = 0; i < samples; ++i)
    {
        closestDepth = texture(pointShadowMaps[lightIndex], toFragmentVector + sampleOffsetDirections[i] * diskRadius).r;
        closestDepth *= farPlane;
        if (currentDepth - bias > closestDepth)
            result += 1.0;
    }

    result /= float(samples);
    */

    float closestDepth = texture(pointShadowMaps[lightIndex], toFragmentVector).r * farPlane;
    if (currentDepth - bias > closestDepth)
        result = 1.0;

    return result;
}
