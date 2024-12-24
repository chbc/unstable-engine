// MAIN_IMPL //
void main()
{
	vec4 vertexPosition = modelMatrix * vec4(in_position, 1.0);
	gl_Position = projectionMatrix * viewMatrix * vertexPosition;
	
	var_textureCoords = in_textureCoords;
}
