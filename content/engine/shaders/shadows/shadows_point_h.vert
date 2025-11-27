// SHADOWS_POINT_H //


// Varying variables
out vec3 var_lightToFragmentVectors[4];

// Uniforms
uniform mat4 directionalLightSpaceMatrix[4];

// Varying variables
out vec4 var_fragPosDirectionalLightSpace[4];

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
void Shadows_setupPointLights(vec4 WorldPos);
