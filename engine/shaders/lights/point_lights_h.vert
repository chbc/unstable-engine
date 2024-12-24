// POINT_LIGHTS_H //

// Types
struct PointLight
{
	vec3 position;
    vec3 color;
    float range;
    float intensity;
};

// Uniforms
const int MAX_POINT_LIGHTS = %d;
uniform PointLight pointLights[MAX_POINT_LIGHTS];

// Varying variables
out vec3 var_toPointLightVectors[MAX_POINT_LIGHTS];

// Functions
void PointLights_setup(vec3 vertexPosition);
