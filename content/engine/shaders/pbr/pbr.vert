layout (location = 0) in vec3 in_position;
layout (location = 1) in vec3 in_normal;
layout (location = 2) in vec2 in_textureCoords;

out vec2 TexCoords;
out vec3 WorldPos;
out vec3 Normal;

// Uniform variables
uniform vec2 uvOffset;
uniform vec2 uvTiling;

// Matrices
uniform mat4 projectionMatrix;
uniform mat4 viewMatrix;
uniform mat4 modelMatrix;
uniform mat3 normalMatrix;

void main()
{
    TexCoords = vec2(uvOffset.x + (in_textureCoords.x * uvTiling.x), uvOffset.y + (in_textureCoords.y * uvTiling.y));
	WorldPos = vec3(modelMatrix * vec4(in_position, 1.0));
    Normal = normalMatrix * in_normal;   

    gl_Position =  projectionMatrix * viewMatrix * vec4(WorldPos, 1.0);
	
	// [DIRECTIONAL_SHADOWS] Shadows_setupDirectionalLights(vec4(WorldPos, 1.0));
	// [POINT_SHADOWS] Shadows_setupPointLights(vec4(WorldPos, 1.0));
}
