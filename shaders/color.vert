#version 140

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
//in vec2 inputUV;

// Varying variables
out vec3 normal;
out vec3 lightDir;
out vec3 lightColor;

void main() 
{
	int tt = lightCount;
	
	normal = (gl_ModelViewProjectionMatrix * vec4(inputNormal, 1.0)).xyz;
	lightDir = lights[0].posDir;
	lightColor = lights[0].color;
	
	gl_Position = gl_ModelViewProjectionMatrix * vec4(vertexPosition, 1.0);
}

/*
void main()
{
	gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;
}
*/