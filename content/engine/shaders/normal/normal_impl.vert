// NORMAL_IMPL //

void Normal_setup()
{
    mat3 normalMatrix = transpose(inverse(mat3(modelMatrix)));
    vec3 tangent    = normalize(normalMatrix * in_tangent);
    vec3 bitangent  = normalize(normalMatrix * in_bitangent);
    vec3 normal     = normalize(normalMatrix * in_normal);

    var_tbnMatrix = transpose(mat3(tangent, bitangent, normal));
}
