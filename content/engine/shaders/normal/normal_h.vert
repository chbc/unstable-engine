// NORMAL_H //

layout(location = 3) in vec3 in_tangent;
layout(location = 4) in vec3 in_bitangent;

// Varying variables
out mat3 var_tbnMatrix;

void Normal_setup();
