// SHADOWS_POINT_H //

// Uniform variables
uniform samplerCube pointShadowMaps[MAX_POINT_LIGHTS];

// Varying variables
in vec3 var_lightToFragmentVectors[MAX_POINT_LIGHTS];

// Functions
float Shadows_computePointLightShadow(int lightIndex);
