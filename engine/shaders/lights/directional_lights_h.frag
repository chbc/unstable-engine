// DIRECTIONAL_LIGHTS_H //

// Types
struct DirectionalLight
{
    vec3 color;
	vec3 direction;
};

// Uniform variables
const int MAX_DIRECTIONAL_LIGHTS = %d;
uniform DirectionalLight directionalLights[MAX_DIRECTIONAL_LIGHTS];

// Varying variables
in vec3 var_directionalLightVectors[MAX_DIRECTIONAL_LIGHTS];

// Functions
void DirectionalLights_compute(vec3 normal, vec3 toCameraDirection, inout vec3 kd, inout vec3 ks);
