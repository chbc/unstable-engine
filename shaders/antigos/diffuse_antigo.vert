varying vec3 normal;
varying vec3 lightDir;

void main()
{
	gl_TexCoord[0] = gl_MultiTexCoord0;
	normal = gl_Normal;
	lightDir = vec3(gl_LightSource[0].position);

	gl_Position = ftransform()
}
