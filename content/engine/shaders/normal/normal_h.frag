// NORMAL_H //

// Uniform variables
uniform sampler2D normalTexture;

// Varying variables
in mat3 var_tbnMatrix;

vec3 Normal_computeNormal();
void Normal_getLightVector(inout vec3 result);
