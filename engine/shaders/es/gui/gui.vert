precision mediump float;

attribute vec2 in_position;
attribute vec2 in_textureCoords;

uniform mat4 modelMatrix;

varying vec2 var_textureCoords;

void main()
{
	var_textureCoords = in_textureCoords;
	gl_Position = modelMatrix * vec4(in_position, 0.0, 1.0);
}
