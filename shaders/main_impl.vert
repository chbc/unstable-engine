// MAIN_IMPL //
void main()
{
	vec4 vertexPosition = modelMatrix * vec4(in_position, 1.0);
	var_normal = (modelMatrix * vec4(in_normal, 0)).xyz;
	
	var_toCameraVector = cameraPosition - vertexPosition.xyz;
	
	// From lights.vert
	Lights_setup(vertexPosition.xyz);

	gl_Position = projectionMatrix * viewMatrix * vertexPosition;
	
	// [DIFFUSE] Diffuse_setup();
	// [NORMAL] Normal_setup();
}
