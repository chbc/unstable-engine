// SHADOWS_H //

// Uniform variables
uniform samplerCube shadowMap;
uniform float farPlane;

// Functions
float Shadows_computeShadow(vec3 toFragmentVector);
