// Vertices
layout(location = 2) in vec2 in_textureCoords;

// Varying variables
out vec2 var_textureCoords;

void Diffuse_setup()
{
	var_textureCoords = in_textureCoords;
}
