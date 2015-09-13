uniform sampler2D texture;

varying vec3 normal;
varying vec3 lightDir;

void main()
{
	// Vectors
	float energy = max(dot(normalize(normal), normalize(lightDir)), 0.0);

	// Colors
	vec4 ka = gl_FrontMaterial.ambient * (gl_LightModel.ambient + gl_LightSource[0].ambient);
	vec4 kd = gl_FrontMaterial.diffuse * gl_LightSource[0].diffuse * energy;
	vec4 kt = texture2D(texture, gl_TexCoord[0].st);
	
	gl_FragColor = (ka + kd) * kt;
}
