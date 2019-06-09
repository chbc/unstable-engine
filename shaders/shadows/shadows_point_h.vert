// SHADOWS_POINT_H //


// Varying variables
out vec3 var_lightToFragmentVectors[MAX_POINT_LIGHTS];

// Functions
void Shadows_setLightToFragmentVector(vec3 value, int index);
