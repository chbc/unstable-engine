// SHADOWS_POINT_H //

// Uniform variables
uniform samplerCube pointShadowMaps[4];

// Varying variables
in vec3 var_lightToFragmentVectors[4];

// Functions
float Shadows_computePointLightShadow(int lightIndex);
