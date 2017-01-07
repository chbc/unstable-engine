#version 400

// Types
struct DirectionalLight
{
	vec3 direction;
	vec3 color;
};

struct PointLight
{
	vec3 position;
	vec3 color;
	float range;
};

struct LightSources
{
	DirectionalLight directionalLights[4]; 
	int directionalLightsCount;
	
	PointLight pointLights[4];
	int pointLightsCount;
	
	vec3 ambientLightColor;
};

// Vertices
layout(location=0) in vec3 in_position;
layout(location=1) in vec3 in_normal;

// Matrices
uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

// Material
uniform vec4 materialColor;

// Camera
uniform vec3 cameraPosition;

// Lights
uniform LightSources lights;

// Varying variables
out vec4 var_position;
out vec3 var_normal;
out vec4 var_materialColor;
out vec3 var_cameraPosition;

out DirectionalLight var_directionalLights[4];
out float var_directionalLightsCount;
out PointLight var_pointLights[4];
out float var_pointLightsCount;
out vec3 var_ambientLightColor;

// Functions
void processLights();

void main(void)
{
	vec4 var_position = modelMatrix * vec4(in_position, 1.0);
	var_cameraPosition = cameraPosition;
	
	var_materialColor = materialColor;
	var_normal = (modelMatrix * vec4(in_normal, 0)).xyz;
	processLights();

	gl_Position = projectionMatrix * viewMatrix * var_position;
}

void processLights()
{
	var_directionalLightsCount = lights.directionalLightsCount;
	var_pointLightsCount = lights.pointLightsCount;
	var_ambientLightColor = lights.ambientLightColor;
	
	for (int i = 0; i < lights.directionalLightsCount; i++)
	{
		var_directionalLights[i].direction = lights.directionalLights[i].direction;
		var_directionalLights[i].color = lights.directionalLights[i].color;
	}
	
	for (int i = 0; i < lights.pointLightsCount; i++)
	{
		var_pointLights[i].position = lights.pointLights[i].position;
		var_pointLights[i].color = lights.pointLights[i].color;
		var_pointLights[i].range = lights.pointLights[i].range;		
	}
}
