// LIGHTS_IMPL //

void Lights_setup(vec3 vertexPosition)
{
	var_toCameraVector = cameraPosition - vertexPosition.xyz;
	
    // [DIRECTIONAL_LIGHTS] DirectionalLights_setup(vertexPosition);
    // [POINT_LIGHTS] PointLights_setup(vertexPosition);
}
