// NORMAL_IMPL //

void Normal_setup()
{
    mat3 normalMatrix = transpose(inverse(mat3(modelMatrix)));
    vec3 tangent    = normalize(normalMatrix * in_tangent);
    vec3 bitangent  = normalize(normalMatrix * in_bitangent);
    vec3 normal     = normalize(normalMatrix * in_normal);

    mat3 tbnMatrix = transpose(mat3(tangent, bitangent, normal));
    var_toCameraVector = tbnMatrix * var_toCameraVector;

    // [DIRECTIONAL_LIGHTS] Normal_setupDirectionalLights(tbnMatrix, MAX_DIRECTIONAL_LIGHTS);
    // [POINT_LIGHTS] Normal_setupPointLights(tbnMatrix, MAX_POINT_LIGHTS);
}
