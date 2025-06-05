// LIGHTS_IMPL //

void Lights_setup(vec3 vertexPosition)
{
	vec4 vec4Position = modelMatrix * vec4(vertexPosition, 1.0);
	var_worldPosition = vec3(vec4Position);
}
