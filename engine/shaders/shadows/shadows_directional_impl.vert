// SHADOWS_DIRECTIONAL_H //

void Shadows_setFragPosDirectionalLightSpace(vec3 vertexPosition, int index)
{
    var_fragPosDirectionalLightSpace[index] = directionalLightSpaceMatrix[index] * vec4(vertexPosition, 1.0);
}
