// SHADOWS_H //

// Uniform variables
// ### uniform samplerCube pointShadowMaps[4];
uniform sampler2D directionalShadowMaps[4];

// Varying variables
in vec3 var_lightToFragmentVectors[4];
in vec4 var_fragPosDirectionalLightSpace[4];

// Functions
float Shadows_computePointLightShadow(int lightIndex);
float Shadows_computeDirectionalLightShadow(vec3 normal, vec3 toLightDirection, int lightIndex);
