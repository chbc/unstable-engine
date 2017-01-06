#version 400

// Types
struct DirectionalLight
{
	vec3 direction;
	vec3 color;
};

// Varying variables
in vec4 var_position;
in vec3 var_normal;
in vec4 var_materialColor;
in DirectionalLight var_directionalLights[4];
in float var_directionalLightsCount;
in vec3 var_ambientLightColor;

// Out variables
out vec4 out_color;

void main(void)
{
	float energy = 0;
	vec3 kd = vec3(0.0);
	
	for (int i = 0; i < var_directionalLightsCount; i++)
	{	
		vec3 lightVector = -var_directionalLights[i].direction;
		vec3 lightColor = var_directionalLights[i].color;
		
		energy = max(dot(normalize(var_normal), normalize(lightVector)), 0.0);
				
		kd = kd + (var_materialColor.rgb * lightColor * energy);
	}

	out_color = vec4(var_ambientLightColor + kd, 1.0);
}
