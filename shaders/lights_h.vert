// LIGHTS_H //

// Types
struct DirectionalLight
{
	vec3 direction;
};

struct PointLight
{
	vec3 position;
};

struct LightSources
{
	DirectionalLight directionalLights[4]; 
	int directionalLightsCount;	
	
	PointLight pointLights[4];
	int pointLightsCount;
};

// Lights
uniform LightSources lights;

// Varying variables
out vec3 var_toPointLightVectors[4];
out vec3 var_directionalLightVectors[4];

void Lights_setup(vec3 vertexPosition);
