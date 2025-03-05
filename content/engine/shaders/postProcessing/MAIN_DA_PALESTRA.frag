...
layout (location = 0) out vec4 out_color;
layout (location = 1) out vec4 out_depth;
...

void main()
{
	...

	out_color = computeColor();
	out_depth = computeDepth();
}
