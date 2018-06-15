// SHADOWS_IMPL
vec3 sampleOffsetDirections[20] = vec3[]
(
    vec3(1, 1, 1), vec3(1, -1, 1), vec3(-1, -1, 1), vec3(-1, 1, 1),
    vec3(1, 1, -1), vec3(1, -1, -1), vec3(-1, -1, -1), vec3(-1, 1, -1),
    vec3(1, 1, 0), vec3(1, -1, 0), vec3(-1, -1, 0), vec3(-1, 1, 0),
    vec3(1, 0, 1), vec3(-1, 0, 1), vec3(1, 0, -1), vec3(-1, 0, -1),
    vec3(0, 1, 1), vec3(0, -1, 1), vec3(0, -1, -1), vec3(0, 1, -1)
);

float Shadows_computeShadow(vec3 toFragmentVector)
{
    float result = 0.0;

    float closestDepth = texture(shadowMap, toFragmentVector).r * farPlane;
    float currentDepth = length(toFragmentVector);

    float bias = 0.15;
    int samples = 20;
    float viewDistance = length(var_toCameraVector);
    float diskRadius = (1.0 + (viewDistance / farPlane)) / farPlane;
        
    for (int i = 0; i < samples; ++i) 
    {
        float closestDepth = texture(shadowMap, toFragmentVector + sampleOffsetDirections[i] * diskRadius).r;
        closestDepth *= farPlane;
        if (currentDepth - bias > closestDepth)
            result += 1.0;
    }

    result /= float(samples);

    return result;
}
