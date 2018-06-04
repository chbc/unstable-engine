// LIGHTS_IMPL

// Functions
void Lights_computeEnergies(vec3 normal, vec3 toCameraDirection, vec3 toLightVector, vec3 lightColor, inout float diffuseEnergy, inout float specularEnergy)
{
    vec3 toLightDirection = normalize(toLightVector);
    vec3 halfVector = normalize(toLightDirection + toCameraDirection);

    float shadow = Lights_computeShadow(normal, toLightDirection);

    diffuseEnergy = max(dot(normal, toLightDirection) * (1 - shadow), 0.0);
    specularEnergy = max(dot(normal, halfVector) * (1 - shadow), 0.0);
    if (specularEnergy > 0.0)
        specularEnergy  = pow(specularEnergy, shininess);
}

void Lights_computeDirectionalLights(vec3 normal, vec3 toCameraDirection, inout vec3 kd, inout vec3 ks)
{
    float diffuseEnergy =  0.0;
    float specularEnergy = 0.0;

    for (int i = 0; i < lights.directionalLightsCount; i++)
    {
        vec3 lightColor = lights.directionalLights[i].color;
        Lights_computeEnergies(normal, toCameraDirection, -var_directionalLightVectors[i], lightColor, diffuseEnergy, specularEnergy);

        kd = kd + (lightColor * diffuseEnergy);
        ks = ks + (vec3(1.0) * specularEnergy);
    }
}
 
void Lights_computePointLights(vec3 normal, vec3 toCameraDirection, inout vec3 kd, inout vec3 ks)
{
    float diffuseEnergy = 0.0;
    float specularEnergy = 0.0;

    for (int i = 0; i < lights.pointLightsCount; i++)
    {
        vec3 lightVector = var_toPointLightVectors[i];
        float distance = length(lightVector);

        if (distance < lights.pointLights[i].range)
        {
            vec3 lightColor = lights.pointLights[i].color;
            Lights_computeEnergies(normal, toCameraDirection, lightVector, lightColor, diffuseEnergy, specularEnergy);

            float attenuation = 1 - (distance / lights.pointLights[i].range);
            attenuation *= lights.pointLights[i].intensity;

            kd = kd + (lightColor * diffuseEnergy * attenuation);
            ks = ks + (vec3(1.0) * specularEnergy * attenuation);
        }
    }
}

vec3 Lights_computeAmbientLight(vec3 materialColor)
{
    return lights.ambientLightColor * materialColor;
}

float Lights_computeShadow(vec3 normal, vec3 toLightDirection)
{
    float result = 0.0;

    vec3 projCoords = var_fragPosLightSpace.xyz / var_fragPosLightSpace.w;
    projCoords = (projCoords * 0.5) + 0.5;
    float closestDepth = texture(shadowMap, projCoords.xy).r;
    float currentDepth = projCoords.z;

    if (currentDepth < 1.0)
    {
        float bias = max(0.05 * (1.0 - dot(normal, toLightDirection)), 0.005);

        vec2 texelSize = 1.0 / textureSize(shadowMap, 0);
        for (int x = -1; x <= 1; ++x)
        {
            for (int y = -1; y <= 1; ++y)
            {
                float pcfDepth = texture(shadowMap, projCoords.xy + vec2(x, y) * texelSize).r;
                result += (currentDepth - bias) > pcfDepth ? 1.0 : 0.0;
            }
        }
        
        result /= 9.0;
    }

    return result;
}
