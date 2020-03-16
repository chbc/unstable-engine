// PARTIAL_BLUR //

uniform bool horizontal;
uniform float weight[5] = float[] (0.227027, 0.1945946, 0.1216216, 0.054054, 0.016216);

vec4 PartialBlur_getColor(vec4 inputColor)
{             
    vec2 tex_offset = 1.0 / textureSize(screenTexture, 0);
    vec3 result = texture(screenTexture, var_textureCoords).rgb * weight[0];
    if (horizontal)
    {
        for(int i = 1; i < 5; ++i)
        {
            result += texture(screenTexture, var_textureCoords + vec2(tex_offset.x * i, 0.0)).rgb * weight[i];
            result += texture(screenTexture, var_textureCoords - vec2(tex_offset.x * i, 0.0)).rgb * weight[i];
        }
    }
    else
    {
        for(int i = 1; i < 5; ++i)
        {
            result += texture(screenTexture, var_textureCoords + vec2(0.0, tex_offset.y * i)).rgb * weight[i];
            result += texture(screenTexture, var_textureCoords - vec2(0.0, tex_offset.y * i)).rgb * weight[i];
        }
    }
	
    return vec4(result, 1.0);
}
