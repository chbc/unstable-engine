// SHADOWS_DIRECTIONAL_H //

// Uniforms
uniform mat4 directionalLightSpaceMatrix[4];

// Varying variables
out vec4 var_fragPosDirectionalLightSpace[4];

// Functions
void Shadows_setupDirectionalLights(vec4 WorldPos);
