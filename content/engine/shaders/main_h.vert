// MAIN_H //

// Vertices
layout(location = 0) in vec3 in_position;
layout(location = 1) in vec3 in_normal;
layout(location = 2) in vec2 in_textureCoords;

// Uniform variables
uniform vec2 uvOffset;
uniform vec2 uvTiling;

// Matrices
uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

// Varying variables
out vec3 var_normal;
out vec2 var_textureCoords;

void main();
