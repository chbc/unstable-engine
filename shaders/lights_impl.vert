// LIGHTS_IMPL //

void Lights_setup(vec3 vertexPosition)
{
	for (int i = 0; i < lights.pointLightsCount; i++)
		var_toPointLightVectors[i] = lights.pointLights[i].position - vertexPosition;	
}
