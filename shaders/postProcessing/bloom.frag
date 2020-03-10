#version 400

// Uniform variables
uniform sampler2D screenTexture;

// Varing variables
in vec2 var_textureCoords;

// Out variables
out vec4 out_color;

void main(void)
{
	vec4 result = texture(screenTexture, var_textureCoords);
	
    float brightness = dot(result.rgb, vec3(0.2126, 0.7152, 0.0722));
    if(brightness > 0.75)
        result = vec4(result.rgb, 1.0);
    else
        result = vec4(0.0, 0.0, 0.0, 1.0);
	
	out_color = result;
}
