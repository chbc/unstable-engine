// Material maps
layout(binding = 1) uniform sampler2D albedoTexture;
layout(binding = 2) uniform sampler2D normalTexture;
layout(binding = 3) uniform sampler2D metallicTexture;
layout(binding = 4) uniform sampler2D roughnessTexture;
layout(binding = 5) uniform sampler2D aoTexture;

// IBL
layout(binding = 6) uniform sampler2D brdfLUT;
layout(binding = 7) uniform samplerCube irradianceMap;
layout(binding = 8) uniform samplerCube prefilterMap;

// Shadows
layout(binding = 11) uniform sampler2D directionalShadowMaps[4];
layout(binding = 15) uniform samplerCube pointShadowMaps[4];

// Uniform variables
uniform vec3 cameraPosition;
uniform float normalFlipGreenChannel;

// Varying variables
in vec4 var_fragPosDirectionalLightSpace[4];

in vec2 TexCoords;
in vec3 WorldPos;
in vec3 Normal;

out vec4 FragColor;

const float PI = 3.14159265359;

// Functions
float Shadows_computeDirectionalLightShadow(vec3 normal, vec3 toLightDirection, int lightIndex);

vec3 getNormalFromMap();
float DistributionGGX(vec3 N, vec3 H, float roughness);
float GeometrySchlickGGX(float NdotV, float roughness);
float GeometrySmith(vec3 N, vec3 V, vec3 L, float roughness);
vec3 fresnelSchlick(float cosTheta, vec3 F0);
vec3 fresnelSchlickRoughness(float cosTheta, vec3 F0, float roughness);
vec3 aces(vec3 x);

void main();
