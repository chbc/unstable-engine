// DEPTH //

// Out variables
layout (location = 1) out vec4 out_depth;

const float NEAR = 0.1;
const float FAR = 100.0;

float LinearizeDepth(float depth) 
{
    float z = depth * 2.0 - 1.0; // back to NDC 
    return (2.0 * NEAR * FAR) / (FAR + NEAR - z * (FAR - NEAR));	
}

void Depth_computeDepth()
{
	float depth = LinearizeDepth(gl_FragCoord.z) / FAR;
	out_depth = vec4(vec3(depth), 1.0);
}
