// MAIN_H //

// Uniform variables
uniform vec4 materialColor;

// Varying variables
in vec3 var_normal;
in vec3 var_toCameraVector;
in vec2 var_textureCoords;

// Out variables
out vec4 out_color;

void main(void);