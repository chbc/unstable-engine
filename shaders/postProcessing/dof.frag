// BLUR //

// Uniform variables
uniform sampler2D depthMap;
uniform float focusNear;
uniform float focusFar;

const float FAR_PLANE_DISTANCE = 100.0;

vec4 DOF_getBlurriedColor(vec4 inputColor)
{
	const float xOffset = 1.0 / (1024.0/4.0);
	const float yOffset = 1.0 / (728.0/4.0);

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

	float normalizedFocusNear = focusNear/FAR_PLANE_DISTANCE;
	float normalizedFocusFar = focusFar/FAR_PLANE_DISTANCE;
	float depthDistance = texture(depthMap, var_textureCoords).r;

	if ((depthDistance < normalizedFocusNear) || (normalizedFocusFar < depthDistance))
		result = DOF_getBlurriedColor(inputColor);

	return result;
}
