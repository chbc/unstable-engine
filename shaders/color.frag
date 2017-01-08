#version 400

// Types
struct DirectionalLight
{
	vec3 direction;
	vec3 color;
};

struct PointLight
{
	vec3 color;
	float range;
	float intensity;
};

struct LightSources
{
	DirectionalLight directionalLights[4]; 
	int directionalLightsCount;
	
	PointLight pointLights[4];
	int pointLightsCount;
	
	vec3 ambientLightColor;
};

// Uniform variables
uniform vec4 materialColor;
uniform float shininess;

uniform LightSources lights;

// Varying variables
in vec3 var_normal;
in vec3 var_toPointLightVectors[4];
in vec3 var_toCameraVector;

// Out variables
out vec4 out_color;

// Functions
void computeDirectionalLights(inout vec3 kd, inout vec3 ks);
void computePointLights(inout vec3 kd, inout vec3 ks);

void main(void)
{
	vec3 ka = lights.ambientLightColor * materialColor.rgb;	
	vec3 kd = vec3(0.0);
	vec3 ks = vec3(0.0);
	computeDirectionalLights(kd, ks);
	computePointLights(kd, ks);

	out_color = vec4(ka + kd + ks, 1.0);
}

void computeDirectionalLights(inout vec3 kd, inout vec3 ks)
{
	float diffuseEnergy =  0.0;
	float specularEnergy = 0.0;
	vec3 normal = normalize(var_normal);
	vec3 toCameraDirection = normalize(var_toCameraVector);
	
	for (int i = 0; i < lights.directionalLightsCount; i++)
	{	
		vec3 lightVector = normalize(-lights.directionalLights[i].direction);
		vec3 lightColor = lights.directionalLights[i].color;
		vec3 halfVector = normalize(lightVector + toCameraDirection);
		
		diffuseEnergy = max(dot(normal, lightVector), 0.0);
		specularEnergy = max(dot(normal, halfVector), 0.0);
		if (specularEnergy > 0.0)
			specularEnergy  = pow(specularEnergy, shininess);		
				
		kd = kd + (materialColor.rgb * lightColor * diffuseEnergy);
		ks = ks + (vec3(1.0) * specularEnergy);
	}
}

void computePointLights(inout vec3 kd, inout vec3 ks)
{
	float diffuseEnergy = 0.0;
	float specularEnergy = 0.0;
	vec3 normal = normalize(var_normal);
	vec3 toCameraDirection = normalize(var_toCameraVector);
	
	for (int i = 0; i < lights.pointLightsCount; i++)
	{	
		vec3 lightVector = var_toPointLightVectors[i];
		float distance = length(lightVector);
		
		if (distance < lights.pointLights[i].range)
		{
			lightVector = normalize(lightVector);
			
			vec3 lightColor = lights.pointLights[i].color;
			vec3 halfVector = normalize(lightVector + toCameraDirection);
			
			diffuseEnergy = max(dot(normal, lightVector), 0.0);
			specularEnergy = max(dot(normal, halfVector), 0.0);
			if (specularEnergy > 0.0)
				specularEnergy  = pow(specularEnergy, shininess);
			
			float attenuation = 1 - (distance / lights.pointLights[i].range);
			attenuation *= lights.pointLights[i].intensity;
					
			kd = kd + (materialColor.rgb * lightColor * diffuseEnergy * attenuation);
			ks = ks + (vec3(1.0) * specularEnergy * attenuation);
		}
	}
}
