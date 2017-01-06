#version 400

// Types
struct DirectionalLight
{
	vec3 direction;
	vec3 color;
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
uniform DirectionalLight directionalLights[4];
uniform int directionalLightsCount;
uniform vec3 ambientLightColor;

// Varying variables
out vec4 var_position;
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
	var_position = mvp * vec4(in_position, 1.0);
	gl_Position = var_position;
}

void processLights()
{
	var_directionalLightsCount = directionalLightsCount;
	var_ambientLightColor = ambientLightColor;
	
	for (int i = 0; i < directionalLightsCount; i++)
	{
		var_directionalLights[i].direction = directionalLights[i].direction;
		var_directionalLights[i].color = directionalLights[i].color;
	}
}
