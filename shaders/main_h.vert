// MAIN_H //

// Vertices
layout(location = 0) in vec3 in_position;
layout(location = 1) in vec3 in_normal;
layout(location = 2) in vec2 in_textureCoords;

// Matrices
uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

// Camera
uniform vec3 cameraPosition;

// Varying variables
out vec3 var_normal;
out vec3 var_toCameraVector;
out vec2 var_textureCoords;

void main();
