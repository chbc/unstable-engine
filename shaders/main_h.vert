// MAIN_H //

// Vertices
layout(location = 0) in vec3 in_position;
layout(location = 1) in vec3 in_normal;

// Matrices
uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

// Camera
uniform vec3 cameraPosition;

// Varying variables
out vec3 var_normal;
out vec3 var_toCameraVector;

void main();
