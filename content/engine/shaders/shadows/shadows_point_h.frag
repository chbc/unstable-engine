// SHADOWS_POINT_H //

// Uniform variables
uniform samplerCube pointShadowMaps[4];

// Varying variables
in vec3 var_lightToFragmentVectors[4];

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
float Shadows_computePointLightShadow(int lightIndex);
