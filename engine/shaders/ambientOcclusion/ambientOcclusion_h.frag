// SPECULAR_H //

// Uniform variables
uniform sampler2D aoTexture;

void AmbientOclusion_computeAO(inout vec3 ka);
