#version 140

in vec3 normal;
in vec3 lightDir;
in vec3 lightColor;

out vec4 outFragment;

void main() 
{ 
	float energy = max(dot(normalize(normal), normalize(lightDir)), 0.0);
	vec3 kd = lightColor * energy;

	outFragment = vec4(kd, 1.0);
}
