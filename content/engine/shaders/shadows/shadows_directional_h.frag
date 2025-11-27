// SHADOWS_DIRECTIONAL_H //

// Uniform variables
uniform sampler2D directionalShadowMaps[4];

// Varying variables
in vec4 var_fragPosDirectionalLightSpace[4];

// Functions
float Shadows_computeDirectionalLightShadow(vec3 normal, vec3 toLightDirection, int lightIndex);
