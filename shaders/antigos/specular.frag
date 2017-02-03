uniform sampler2D texture;

varying vec3 normal;
varying vec3 halfVector;

void main()
{
	// Vectors
	vec3 lightDir = vec3(gl_LightSource[0].position);
	vec3 fragNormal = normalize(normal);
	vec3 fragHalfVector = normalize(halfVector);
	float diffuseEnergy = max(dot(fragNormal, lightDir), 0.0);

	// Colors
	vec4 kt = texture2D(texture, gl_TexCoord[0].st);	
	vec4 ka = gl_FrontMaterial.ambient * (gl_LightModel.ambient + gl_LightSource[0].ambient);
	vec4 color = ka * kt;
	
	if (diffuseEnergy > 0.0)
	{
		float specularEnergy = max(dot(fragNormal, fragHalfVector), 0.0);

		// Colors
		vec4 kd = gl_FrontMaterial.diffuse * gl_LightSource[0].diffuse * diffuseEnergy;
		vec4 ks = gl_FrontMaterial.specular * gl_LightSource[0].specular * specularEnergy;
		ks *= pow(specularEnergy, gl_FrontMaterial.shininess);
		
		color = (ka + kd + ks) * kt;
	}
	
	gl_FragColor = color;
}
