layout (location = 0) in vec3 in_position;
layout (location = 1) in vec3 in_normal;
layout (location = 2) in vec2 in_textureCoords;

out vec2 TexCoords;
out vec3 WorldPos;
out vec3 Normal;

// Uniform variables
uniform vec2 uvOffset;
uniform vec2 uvTiling;
uniform mat4 directionalLightSpaceMatrix[4];

// Matrices
uniform mat4 projectionMatrix;
uniform mat4 viewMatrix;
uniform mat4 modelMatrix;
uniform mat3 normalMatrix;

// Varying variables
out vec3 var_lightToFragmentVectors[4];
out vec4 var_fragPosDirectionalLightSpace[4];

// Functions
void Shadows_setupDirectionalLights(vec4 WorldPos);
void Shadows_setupPointLights(vec4 WorldPos);
void main();
