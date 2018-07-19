// SHADOWS_H //

// Uniform variables
uniform sampler2D directionalShadowMaps[4];
// ### POINT LIGHT uniform samplerCube pointShadowMaps[4];

// Varying variables
in vec4 var_fragPosDirectionalLightSpace[4];
// ### POINT LIGHT in vec3 var_lightToFragmentVectors[4];

// Functions
// ### POINT LIGHT float Shadows_computePointLightShadow(int lightIndex);
float Shadows_computeDirectionalLightShadow(vec3 normal, vec3 toLightDirection, int lightIndex);
