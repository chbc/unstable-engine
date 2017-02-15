// DIFFUSE_H //

// Uniform variables
uniform sampler2D diffuseTexture;

// Varying variables
in vec2 var_textureCoords;

vec4 Diffuse_computeTextureColor(vec3 ka, vec3 kd, vec3 ks);
