// MAIN_IMPL //
void main()
{
	vec4 vertexPosition = modelMatrix * vec4(in_position, 1.0);
	var_normal = (modelMatrix * vec4(in_normal, 0)).xyz;
		
	// From lights.vert
	// [LIGHTS] Lights_setup(vertexPosition.xyz);

	gl_Position = projectionMatrix * viewMatrix * vertexPosition;
	
	var_textureCoords = vec2(uvOffset.x + (in_textureCoords.x * uvTiling.x), uvOffset.y + (in_textureCoords.y * uvTiling.y));
	// [NORMAL] Normal_setup();
}
