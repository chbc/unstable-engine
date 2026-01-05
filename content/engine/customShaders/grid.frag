#version 330

layout (location = 0) out vec4 out_color;

in vec3 worldPosition;

void main(void)
{
    float scale = 1.0;
    vec2 coord = worldPosition.xz * scale; 
    vec2 grid = abs(fract(coord - 0.5) - 0.5) / fwidth(coord);
	
    float line = min(grid.x, grid.y);
    float color = 1.0 - min(line, 1.0);
    float opacity = color * 0.3; 

	vec4 resultColor = vec4(0.5, 0.5, 0.5, opacity);

    if (opacity < 0.1)
	{
		discard;
	}
	else if (abs(worldPosition.x) < 0.02)
	{
		resultColor = vec4(0.0, 0.0, 1.0, opacity * 2.0);
	}
	else if (abs(worldPosition.z) < 0.02)
	{
		resultColor = vec4(1.0, 0.0, 0.0, opacity * 2.0);
	}

    out_color = resultColor;
}
