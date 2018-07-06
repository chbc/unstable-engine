// SHADOWS_H //

// Uniforms
uniform mat4 directionalLightSpaceMatrix[4];

// Varying variables
out vec3 var_lightToFragmentVectors[4];
out vec4 var_fragPosDirectionalLightSpace[4];
