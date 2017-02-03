#version 400

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

// Vertices
layout(location = 0) in vec3 in_position;
layout(location = 1) in vec3 in_normal;

// Matrices
uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

// Lights
uniform LightSources lights;

// Camera
uniform vec3 cameraPosition;

// Varying variables
out vec3 var_normal;
out vec3 var_toCameraVector;
out vec3 var_toPointLightVectors[4];

void main(void)
{
	vec4 vertexPosition = modelMatrix * vec4(in_position, 1.0);
	var_normal = (modelMatrix * vec4(in_normal, 0)).xyz;
	
	var_toCameraVector = cameraPosition - vertexPosition.xyz;
	
	for (int i = 0; i < lights.pointLightsCount; i++)
		var_toPointLightVectors[i] = lights.pointLights[i].position - vertexPosition.xyz;

	gl_Position = projectionMatrix * viewMatrix * vertexPosition;
}
