// BLUR //

// Uniform variables
uniform sampler2D depthMap;
uniform float focusNear;
uniform float focusFar;

vec4 DOF_getBlurriedColor(vec4 inputColor)
{
	const float xOffset = 1.0/512.0;
	const float yOffset = 1.0/364.0;

    vec2 offsets[9] = vec2[]
	(
        vec2(-xOffset, yOffset), 	vec2(0.0f, yOffset), 	vec2(xOffset, yOffset),
        vec2(-xOffset, 0.0f), 		vec2(0.0f, 0.0f), 		vec2(xOffset, 0.0f),
        vec2(-xOffset, -yOffset),	vec2(0.0f, -yOffset),	vec2(xOffset, -yOffset)
    );

	float kernel[9] = float[]
	(
		1.0/16,	2.0/16, 1.0/16,
		2.0/16,	4.0/16, 2.0/16,
		1.0/16,	2.0/16, 1.0/16  
	);
    
    vec4 result = vec4(0.0);
    for(int i = 0; i < 9; i++)
    {
         result += texture(screenTexture, var_textureCoords.st + offsets[i]) * kernel[i];
    }

	return result;
}

vec4 DOF_getColor(vec4 inputColor)
{

	vec4 result = inputColor;
	
	float depthDistance = texture(depthMap, var_textureCoords).r;
	if ((depthDistance < focusNear) || (depthDistance > focusFar))
		result = DOF_getBlurriedColor(inputColor);
	
	return result;
}
