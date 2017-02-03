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
void computeEnergies(vec3 normal, vec3 toCameraDirection, vec3 toLightVector, vec3 lightColor, inout float diffuseEnergy, inout float specularEnergy)
{
		vec3 toLightDirection = normalize(toLightVector);
		vec3 halfVector = normalize(toLightDirection + toCameraDirection);
		
		diffuseEnergy = max(dot(normal, toLightDirection), 0.0);
		specularEnergy = max(dot(normal, halfVector), 0.0);
		if (specularEnergy > 0.0)
			specularEnergy  = pow(specularEnergy, shininess);		
}

void computeDirectionalLights(vec3 normal, vec3 toCameraDirection, inout vec3 kd, inout vec3 ks)
{
	float diffuseEnergy =  0.0;
	float specularEnergy = 0.0;
	
	for (int i = 0; i < lights.directionalLightsCount; i++)
	{
		vec3 lightColor = lights.directionalLights[i].color;
		computeEnergies(normal, toCameraDirection, -lights.directionalLights[i].direction, lightColor, diffuseEnergy, specularEnergy);
				
		kd = kd + (lightColor * diffuseEnergy);
		ks = ks + (vec3(1.0) * specularEnergy);
	}
}
 
void computePointLights(vec3 normal, vec3 toCameraDirection, inout vec3 kd, inout vec3 ks)
{
	float diffuseEnergy = 0.0;
	float specularEnergy = 0.0;
	
	for (int i = 0; i < lights.pointLightsCount; i++)
	{	
		vec3 lightVector = var_toPointLightVectors[i];
		float distance = length(lightVector);
		
		if (distance < lights.pointLights[i].range)
		{
			vec3 lightColor = lights.pointLights[i].color;
			computeEnergies(normal, toCameraDirection, lightVector, lightColor, diffuseEnergy, specularEnergy);
			
			float attenuation = 1 - (distance / lights.pointLights[i].range);
			attenuation *= lights.pointLights[i].intensity;
					
			kd = kd + (lightColor * diffuseEnergy * attenuation);
			ks = ks + (vec3(1.0) * specularEnergy * attenuation);
		}
	}
}

void main(void)
{
	vec3 ka = lights.ambientLightColor * materialColor.rgb;	
	vec3 kd = vec3(0.0);
	vec3 ks = vec3(0.0);
	
	vec3 normal = normalize(var_normal);
	vec3 toCameraDirection = normalize(var_toCameraVector);	
	
	computeDirectionalLights(normal, toCameraDirection, kd, ks);
	computePointLights(normal, toCameraDirection, kd, ks);

	kd = kd * materialColor.rgb;
	ks = ks * materialColor.rgb;
	
	out_color = vec4(ka + kd + ks, 1.0);
}

