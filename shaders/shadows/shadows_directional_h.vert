// SHADOWS_DIRECTIONAL_H //

// Uniforms
uniform mat4 directionalLightSpaceMatrix[MAX_DIRECTIONAL_LIGHTS];

// Varying variables
out vec4 var_fragPosDirectionalLightSpace[MAX_DIRECTIONAL_LIGHTS];

// Functions
void Shadows_setFragPosDirectionalLightSpace(vec3 vertexPosition, int index);
