// HDR //

vec4 HDR_getColor(vec4 inputColor)
{
	const float gamma = 2.2;
	const float exposure = 0.1; // ###
	
	vec3 result = inputColor.rgb;
	
	result = vec3(1.0) - exp(-result * exposure);
	result = pow(result, vec3(1.0 / gamma));
	
	return vec4(result, 1.0);
}
