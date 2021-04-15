precision mediump float;

uniform sampler2D guiTexture;

varying vec2 var_textureCoords;

void main(void)
{
	gl_FragColor = texture2D(guiTexture, var_textureCoords);
}
