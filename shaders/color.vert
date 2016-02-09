#version 140

uniform mat4 MVP;

// Lights
uniform struct
{
	vec3 posDir;
	vec3 color;
	int type;
} lights[];

uniform int lightCount;

// Input attributes
in vec3 vertexPosition;
in vec3 inputNormal;

// Varying variables
out vec3 normal;
out vec3 lightDir;
out vec3 lightColor;

void main()
{
	int tt = lightCount;
	
	normal = normalize(inputNormal);
	lightDir = lights[0].posDir;
	lightColor = lights[0].color;
	
	gl_Position = MVP * vec4(vertexPosition, 1.0);
}
