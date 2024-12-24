// MAIN_H //

precision mediump float;

// Vertices
attribute vec3 in_position;
attribute vec2 in_textureCoords;

// Matrices
uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

// Varying variables
varying vec2 var_textureCoords;
