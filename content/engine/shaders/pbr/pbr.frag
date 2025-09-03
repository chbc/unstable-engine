// Uniform variables
uniform sampler2D albedoTexture;
uniform sampler2D normalTexture;
uniform sampler2D metallicTexture;
uniform sampler2D roughnessTexture;
uniform sampler2D aoTexture;

uniform vec3 ambientLightColor;
uniform float shininess;

// Varying variables
out vec4 FragColor;
in vec2 TexCoords;
in vec3 WorldPos;
in vec3 Normal;

uniform vec3 cameraPosition;

const float PI = 3.14159265359;

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

    int maxDirectionalLights;
    int maxPointLights;
};

// ----------------------------------------------------------------------------
// Easy trick to get tangent-normals to world-space to keep PBR code simplified.
// Don't worry if you don't get what's going on; you generally want to do normal 
// mapping the usual way for performance anyways; I do plan make a note of this 
// technique somewhere later in the normal mapping tutorial.
vec3 getNormalFromMap()
{
    vec3 tangentNormal = texture(normalTexture, TexCoords).xyz * 2.0 - 1.0;

    vec3 Q1  = dFdx(WorldPos);
    vec3 Q2  = dFdy(WorldPos);
    vec2 st1 = dFdx(TexCoords);
    vec2 st2 = dFdy(TexCoords);

    vec3 N   = normalize(Normal);
    vec3 T  = normalize(Q1*st2.t - Q2*st1.t);
    vec3 B  = -normalize(cross(N, T));
    mat3 TBN = mat3(T, B, N);

    return normalize(TBN * tangentNormal);
}
// ----------------------------------------------------------------------------
float DistributionGGX(vec3 N, vec3 H, float roughness)
{
    float a = roughness*roughness;
    float a2 = a*a;
    float NdotH = max(dot(N, H), 0.0);
    float NdotH2 = NdotH*NdotH;

    float nom   = a2;
    float denom = (NdotH2 * (a2 - 1.0) + 1.0);
    denom = PI * denom * denom;

    return nom / denom;
}
// ----------------------------------------------------------------------------
float GeometrySchlickGGX(float NdotV, float roughness)
{
    float r = (roughness + 1.0);
    float k = (r*r) / 8.0;

    float nom   = NdotV;
    float denom = NdotV * (1.0 - k) + k;

    return nom / denom;
}
// ----------------------------------------------------------------------------
float GeometrySmith(vec3 N, vec3 V, vec3 L, float roughness)
{
    float NdotV = max(dot(N, V), 0.0);
    float NdotL = max(dot(N, L), 0.0);
    float ggx2 = GeometrySchlickGGX(NdotV, roughness);
    float ggx1 = GeometrySchlickGGX(NdotL, roughness);

    return ggx1 * ggx2;
}
// ----------------------------------------------------------------------------
vec3 fresnelSchlick(float cosTheta, vec3 F0)
{
    return F0 + (1.0 - F0) * pow(clamp(1.0 - cosTheta, 0.0, 1.0), 5.0);
}
// ----------------------------------------------------------------------------
void computeDiffuseSpecular(vec3 V, vec3 N, vec3 L, vec3 F0, float roughness, float metallic, out vec3 kD, out vec3 specular)
{
	// Cook-Torrance BRDF
	vec3 H = normalize(V + L);
	float NDF = DistributionGGX(N, H, roughness);   
	float G   = GeometrySmith(N, V, L, roughness);      
	vec3 F    = fresnelSchlick(max(dot(H, V), 0.0), F0);
	   
	vec3 numerator    = NDF * G * F * shininess; // XXX
	float denominator = 4.0 * max(dot(N, V), 0.0) * max(dot(N, L), 0.0) + 0.0001; // + 0.0001 to prevent divide by zero
	specular = numerator / denominator;
	
	// kS is equal to Fresnel
	vec3 kS = F;
	// for energy conservation, the diffuse and specular light can't
	// be above 1.0 (unless the surface emits light); to preserve this
	// relationship the diffuse component (kD) should equal 1.0 - kS.
	kD = vec3(1.0) - kS;
	// multiply kD by the inverse metalness such that only non-metals 
	// have diffuse lighting, or a linear blend if partly metal (pure metals
	// have no diffuse light).
	kD *= 1.0 - metallic;	  
}
// ----------------------------------------------------------------------------
void main()
{
    vec3 albedo     = pow(texture(albedoTexture, TexCoords).rgb, vec3(2.2));
    float metallic  = texture(metallicTexture, TexCoords).b;
    float roughness = texture(roughnessTexture, TexCoords).g;
    float ao        = texture(aoTexture, TexCoords).r;

    vec3 N = getNormalFromMap();
    vec3 V = normalize(cameraPosition - WorldPos);

    // calculate reflectance at normal incidence; if dia-electric (like plastic) use F0 
    // of 0.04 and if it's a metal, use the albedo color as F0 (metallic workflow)    
    vec3 F0 = vec3(0.04); 
    F0 = mix(F0, albedo, metallic);

    // reflectance equation
    vec3 Lo = vec3(0.0);
	
    for(int i = 0; i < maxDirectionalLights; ++i) 
    {
        // calculate per-light radiance
		vec3 toLight = -vec3(directionalLights[i].direction);
        vec3 L = normalize(toLight);
		vec3 radiance = vec3(directionalLights[i].color);
		
		vec3 kD;
		vec3 specular;
		computeDiffuseSpecular(V, N, L, F0, roughness, metallic, kD, specular);

		// scale light by NdotL
		float NdotL = max(dot(N, L), 0.0);        

		// add to outgoing radiance Lo
		Lo += (kD * albedo / PI + specular) * radiance * NdotL;  // note that we already multiplied the BRDF by the Fresnel (kS) so we won't multiply by kS again
    }
	
    for(int i = 0; i < maxPointLights; ++i) 
    {
        // calculate per-light radiance
		vec3 toLight = vec3(pointLights[i].position) - WorldPos;
        vec3 L = normalize(toLight);
        float distance = length(toLight);

		float attenuation = 1.0 / (distance * distance);
		float range = pointLights[i].rangeAndIntensity.x;
		float intensity = pointLights[i].rangeAndIntensity.y;
		attenuation *= range * intensity; // XXX
		vec3 radiance = vec3(pointLights[i].color) * attenuation; // XXX
		
		vec3 kD;
		vec3 specular;
		computeDiffuseSpecular(V, N, L, F0, roughness, metallic, kD, specular);

		// scale light by NdotL
		float NdotL = max(dot(N, L), 0.0);        

		// add to outgoing radiance Lo
		Lo += (kD * albedo / PI + specular) * radiance * NdotL;  // note that we already multiplied the BRDF by the Fresnel (kS) so we won't multiply by kS again
    }
	
    // ambient lighting (note that the next IBL tutorial will replace 
    // this ambient lighting with environment lighting).
    vec3 ambient = ambientLightColor * albedo * ao;
    
    vec3 color = ambient + Lo;

    // HDR tonemapping
    color = color / (color + vec3(1.0));
    // gamma correct
    color = pow(color, vec3(1.0/2.2)); 

    FragColor = vec4(color, 1.0);
}
