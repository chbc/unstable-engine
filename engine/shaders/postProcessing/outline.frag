// OUTLINE //

vec4 Outline_getColor(vec4 inputColor)
{
	const vec2 size = vec2(1024.0, 728.0);
	float xOffset = 1.0/size.x;
	float yOffset = 1.0/size.y;

    vec2 offsets[9] = vec2[]
	(
        vec2(-xOffset, yOffset), 	vec2(0.0f, yOffset), 	vec2(xOffset, yOffset),
        vec2(-xOffset, 0.0f), 		vec2(0.0f, 0.0f), 		vec2(xOffset, 0.0f),
        vec2(-xOffset, -yOffset),	vec2(0.0f, -yOffset),	vec2(xOffset, -yOffset)
    );

	float kernel[9] = float[]
	(
		1.0,	1.0, 	1.0,
		1.0,	-8.0, 	1.0,
		1.0,	1.0, 	1.0  
	);
    
    float result = 0;

    for(int i = 0; i < 9; i++)
    {
		vec4 color = texture(screenTexture, var_textureCoords.st + offsets[i]);
        result += color.r * kernel[i];
    }

	return vec4(0.0, result, 0.0, 1.0);
}
