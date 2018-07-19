// SHADOWS_H //

// Uniforms
uniform mat4 directionalLightSpaceMatrix[4];

// Varying variables
out vec4 var_fragPosDirectionalLightSpace[4];
// ### POINT LIGHT out vec3 var_lightToFragmentVectors[4];

// Functions
void Shadows_setFragPosDirectionalLightSpace(vec3 vertexPosition, int index);
// ### POINT LIGHT void Shadows_setLightToFragmentVector(vec3 value, int index);
