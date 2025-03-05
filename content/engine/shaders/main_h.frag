// MAIN_H //

// Uniform variables
uniform vec4 materialColor;

// Varying variables
in vec3 var_normal;
in vec2 var_textureCoords;

// Out variables
layout (location = 0) out vec4 out_color;

void main(void);
