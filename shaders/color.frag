#version 400

// Types
struct DirectionalLight
{
	vec3 direction;
	vec3 color;
};

struct PointLight
{
	vec3 position;
	vec3 color;
	float range;
};

// Varying variables
in vec4 var_position;
in vec3 var_normal;
in vec3 var_cameraPosition;
in vec4 var_materialColor;

in DirectionalLight var_directionalLights[4];
in float var_directionalLightsCount;
in PointLight var_pointLights[4];
in float var_pointLightsCount;
in vec3 var_ambientLightColor;

// Out variables
out vec4 out_color;

void computeDirectionalLights(inout vec3 kd, inout vec3 ks);
void computePointLights(inout vec3 kd, inout vec3 ks);

void main(void)
{
	vec3 kd = vec3(0.0);
	vec3 ks = vec3(0.0);
	computeDirectionalLights(kd, ks);
	computePointLights(kd, ks);

	out_color = vec4(var_ambientLightColor + kd + ks, 1.0);
}

void computeDirectionalLights(inout vec3 kd, inout vec3 ks)
{
	float diffuseEnergy = 0.0;
	float specularEnergy = 0.0;
	vec3 normal = normalize(var_normal);
	vec3 toCameraDirection = normalize(var_cameraPosition - var_position.xyz);
	
	float ttShininess = 15.0;
	
	for (int i = 0; i < var_directionalLightsCount; i++)
	{	
		vec3 lightVector = normalize(-var_directionalLights[i].direction);
		vec3 lightColor = var_directionalLights[i].color;
		vec3 halfVector = normalize(lightVector + toCameraDirection);
		
		diffuseEnergy = max(dot(normal, lightVector), 0.0);
		specularEnergy = max(dot(normal, halfVector), 0.0);
		if (specularEnergy > 0.0)
			specularEnergy  = pow(specularEnergy, ttShininess);		
				
		kd = kd + (var_materialColor.rgb * lightColor * diffuseEnergy);
		ks = ks + (vec3(1.0) * specularEnergy);
	}	
}

void computePointLights(inout vec3 kd, inout vec3 ks)
{
	float diffuseEnergy = 0.0;
	float specularEnergy = 0.0;
	vec3 normal = normalize(var_normal);
	vec3 toCameraDirection = normalize(var_cameraPosition - var_position.xyz);
	
	float ttShininess = 15.0;
	
	for (int i = 0; i < var_pointLightsCount; i++)
	{	
		vec3 lightVector = var_pointLights[i].position - var_position.xyz;
		float distance = length(lightVector);
		lightVector = normalize(lightVector);
		
		vec3 lightColor = var_pointLights[i].color;
		vec3 halfVector = normalize(lightVector + toCameraDirection);
		
		diffuseEnergy = max(dot(normal, lightVector), 0.0);
		specularEnergy = max(dot(normal, halfVector), 0.0);
		if (specularEnergy > 0.0)
			specularEnergy  = pow(specularEnergy, ttShininess);
		
		float attenuation = 1.0 / (distance * distance);
				
		kd = kd + (var_materialColor.rgb * lightColor * diffuseEnergy * attenuation);
		ks = ks + (vec3(1.0) * specularEnergy * attenuation);
	}	
}