#version 120

varying vec4 diffuse, ambient;
varying vec3 normal, halfVector;

void main()
{
	gl_TexCoord[0] = gl_MultiTexCoord0;
	normal = gl_Normal;
	halfVector = gl_LightSource[0].halfVector.xyz;
	
	gl_Position = ftransform();
}
