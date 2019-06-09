// DIRECTIONAL_LIGHTS_H //

// Types
struct DirectionalLight
{
    vec3 direction;
};

// Uniforms
const int MAX_DIRECTIONAL_LIGHTS = %d;
uniform DirectionalLight directionalLights[MAX_DIRECTIONAL_LIGHTS];

// Varying variables
out vec3 var_directionalLightVectors[MAX_DIRECTIONAL_LIGHTS];

// Functions
void DirectionalLights_setup(vec3 vertexPosition);
