#version 400

// #################
// Types
struct PointLight
{
	vec3 position;
};

struct LightSources
{
	PointLight pointLights[4];
	int pointLightsCount;
};

// Uniform variables
uniform LightSources lights;

// Varying variables
out vec3 var_toPointLightVectors[4];

void vert_setupLights()
{
	for (int i = 0; i < lights.pointLightsCount; i++)
		var_toPointLightVectors[i] = lights.pointLights[i].position - vertexPosition.xyz;	
}

// #################

// Vertices
layout(location=0) in vec3 in_position;
layout(location=1) in vec3 in_normal;
layout(location=2) in vec2 in_textureCoords;

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

void main(void)
{
	vec4 vertexPosition = modelMatrix * vec4(in_position, 1.0);
	var_normal = (modelMatrix * vec4(in_normal, 0)).xyz;
	var_toCameraVector = cameraPosition - vertexPosition.xyz;

	var_textureCoords = in_textureCoords;
	
	gl_Position = projectionMatrix * viewMatrix * vertexPosition;
	
	vert_setupLights();
}
