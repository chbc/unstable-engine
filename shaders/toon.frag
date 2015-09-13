uniform sampler2D texture;
uniform int layersCount;

varying vec3 normal;

void main()
{
	// Vectors
	vec3 lightDir = vec3(gl_LightSource[0].position);
	vec3 fragNormal = normalize(normal);
	float diffuseEnergy = max(dot(fragNormal, lightDir), 0.0);

	// Colors source
	vec4 ka = gl_FrontMaterial.ambient * (gl_LightModel.ambient + gl_LightSource[0].ambient);
	vec4 color = ka;
	
	if (diffuseEnergy > 0.0)
	{
		if (diffuseEnergy > 0.75)
			diffuseEnergy = 1.0;
		else if (diffuseEnergy > 0.5)
			diffuseEnergy = 0.75;
		else
			diffuseEnergy = 0.0;
	
		// Colors
		vec4 kd = gl_FrontMaterial.diffuse * gl_LightSource[0].diffuse * diffuseEnergy;
		vec4 kt = texture2D(texture, gl_TexCoord[0].st);
	
		color = (ka + kd) * kt;
	}
	
	gl_FragColor = color;
}
