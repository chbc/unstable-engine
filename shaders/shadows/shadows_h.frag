// SHADOWS_H //

// Uniform variables
uniform samplerCube shadowMaps[2];
uniform float farPlane;

// Functions
float Shadows_computeShadow(vec3 toFragmentVector, int XXX_lightIndex);
