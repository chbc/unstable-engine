// LIGHTS_H //

// Uniform variables
uniform vec3 cameraPosition;
uniform float shininess;

// Varying variables
in vec3 var_worldPosition;

// UBO
struct DirectionalLight
{
	vec4 direction;
    vec4 color;
};

struct PointLight
{
	vec4 position;
    vec4 color;
	vec4 rangeAndIntensity;
};

layout (std140, binding = 0) uniform LightsBuffer
{
	DirectionalLight directionalLights[4];
	PointLight pointLights[4];

	vec4 ambientLightColor;
    int maxDirectionalLights;
    int maxPointLights;
};

// Functions
vec3 Lights_computeAmbientLight(vec3 materialColor);
void Lights_computeDiffuseAndSpecularLights(vec3 normal, inout vec3 kd, inout vec3 ks);
void Lights_computeEnergies(vec3 normal, vec3 toCameraDirection, vec3 toLightVector, inout float diffuseEnergy, inout float specularEnergy);

void DirectionalLights_compute(vec3 normal, vec3 toCameraDirection, inout vec3 kd, inout vec3 ks);

void PointLights_compute(vec3 normal, vec3 toCameraDirection, inout vec3 kd, inout vec3 ks);
float PointLights_getAttenuation(int lightIndex, vec3 toPointLightVector);
