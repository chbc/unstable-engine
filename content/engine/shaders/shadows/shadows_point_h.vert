// SHADOWS_POINT_H //


// Varying variables
out vec3 var_lightToFragmentVectors[4];

// Uniforms
uniform mat4 directionalLightSpaceMatrix[4];

// Varying variables
out vec4 var_fragPosDirectionalLightSpace[4];

// Functions
void Shadows_setupPointLights(vec4 WorldPos);
