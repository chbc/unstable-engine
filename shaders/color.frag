#version 400

in vec4 var_position;
in vec3 var_normal;
in vec4 var_materialColor;
in vec3 var_lightDirection;


out vec4 out_color;

void main(void)
{
	vec3 lightVector = -var_lightDirection;
	float energy = max(dot(normalize(var_normal), normalize(lightVector)), 0.0);
	vec3 kd = var_materialColor.rgb * energy;

	out_color = vec4(kd, 1.0);	
}
