// Uniform variables
uniform sampler2D diffuseTexture;

// Varying variables
in vec2 var_textureCoords;

vec4 Diffuse_computeTextureColor(vec3 ka, vec3 kd, vec3 ks)
{
	vec3 kt = texture(diffuseTexture, var_textureCoords).rgb;
	vec3 resultColor = (ka * kt) + (kd * kt) + ks;
	
	return vec4(resultColor, 1.0);
}
