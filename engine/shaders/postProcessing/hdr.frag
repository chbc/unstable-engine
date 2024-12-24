// HDR //

uniform float exposure;
uniform float enabled;

vec4 HDR_getColor(vec4 inputColor)
{
	vec3 result = inputColor.rgb;

	if (enabled > 0.0)
	{
		const float gamma = 2.2;
		
		result = vec3(1.0) - exp(-result * exposure);
		result = pow(result, vec3(1.0 / gamma));
	}
	
	return vec4(result, 1.0);
}
