// BLOOM //

// Out variables
layout (location = 1) out vec4 out_brightness;

void Bloom_computeBloom(vec4 inputColor)
{
    float brightness = dot(inputColor.rgb, vec3(0.2126, 0.7152, 0.0722));
	
    if (brightness > 0.9f)
        out_brightness = vec4(inputColor.rgb, 1.0);
    else
        out_brightness = vec4(0.0, 0.0, 0.0, 1.0);
}
