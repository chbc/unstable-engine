// SHADOWS_DIRECTIONAL_H //

// Uniform variables
uniform sampler2D directionalShadowMaps[MAX_DIRECTIONAL_LIGHTS];

// Varying variables
in vec4 var_fragPosDirectionalLightSpace[MAX_DIRECTIONAL_LIGHTS];

// Functions
float Shadows_computeDirectionalLightShadow(vec3 normal, vec3 toLightDirection, int lightIndex);
