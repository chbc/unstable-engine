#version 400

// Types
struct DirectionalLight
{
	vec3 direction;
	vec3 color;
};
	
struct Lights
{
	DirectionalLight directionalLights[4]; 
	int directionalLightsCount;
	vec3 ambientLightColor;
};

// Vertices
layout(location=0) in vec3 in_position;
layout(location=1) in vec3 in_normal;

// Matrices
uniform mat4 viewProjectionMatrix;
uniform mat4 modelMatrix;

// Material
uniform vec4 materialColor;

// Lights
uniform Lights lights;

// Varying variables
out vec3 var_normal;
out vec4 var_materialColor;
out DirectionalLight var_directionalLights[4];
out float var_directionalLightsCount;
out vec3 var_ambientLightColor;

// Functions
void processLights();

void main(void)
{
	var_materialColor = materialColor;
	var_normal = (modelMatrix * vec4(in_normal, 0)).xyz;
	processLights();
	
	mat4 mvp = viewProjectionMatrix * modelMatrix;
	gl_Position = mvp * vec4(in_position, 1.0);
}

void processLights()
{
	var_directionalLightsCount = lights.directionalLightsCount;
	var_ambientLightColor = lights.ambientLightColor;
	
	for (int i = 0; i < lights.directionalLightsCount; i++)
	{
		var_directionalLights[i].direction = lights.directionalLights[i].direction;
		var_directionalLights[i].color = lights.directionalLights[i].color;
	}
}
