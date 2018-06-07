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

    vec3 ambientLightColor;
};

// Lights
uniform LightSources lights;
uniform mat4 lightSpaceMatrix;

// Varying variables
out vec3 var_toPointLightVectors[4];
out vec3 var_directionalLightVectors[4];
out vec4 var_fragPosLightSpace;

void Lights_setup(vec3 vertexPosition);
