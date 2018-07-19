// SHADOWS_H //

void Shadows_setFragPosDirectionalLightSpace(vec3 vertexPosition, int index)
{
    var_fragPosDirectionalLightSpace[index] = directionalLightSpaceMatrix[index] * vec4(vertexPosition, 1.0);
}

/* ### CHAMADO POR POINT LIGHT
void Shadows_setLightToFragmentVector(vec3 value, int index)
{
    var_lightToFragmentVectors[i] = vertexPosition - pointLights[i].position;
}
*/
