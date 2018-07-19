// LIGHTS_H //

struct PointLight
{
    vec3 color;
    float range;
    float intensity;
};

// Uniform variables
const int MAX_POINT_LIGHTS = %d;
uniform PointLight pointLights[MAX_POINT_LIGHTS];

// Varying variables
in vec3 var_toPointLightVectors[MAX_DIRECTIONAL_LIGHTS];

// Functions
void PointLights_compute(vec3 normal, vec3 toCameraDirection, inout vec3 kd, inout vec3 ks);
float PointLights_getAttenuation(int lightIndex);
