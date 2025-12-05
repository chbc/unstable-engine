void Shadows_setupDirectionalLights(vec4 WorldPos)
{
	for (int i = 0; i < maxDirectionalLights; ++i)
	{
		var_fragPosDirectionalLightSpace[i] = directionalLightSpaceMatrix[i] * WorldPos;
	}
}

void main()
{
    TexCoords = vec2(uvOffset.x + (in_textureCoords.x * uvTiling.x), uvOffset.y + (in_textureCoords.y * uvTiling.y));
	WorldPos = vec3(modelMatrix * vec4(in_position, 1.0));
    Normal = normalMatrix * in_normal;   

    gl_Position =  projectionMatrix * viewMatrix * vec4(WorldPos, 1.0);
	
	Shadows_setupDirectionalLights(vec4(WorldPos, 1.0));
}
