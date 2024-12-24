#version 330 core

uniform sampler2D shadowMap;

out vec4 FragColor;
in vec2 TexCoords;

void main()
{
    float depthValue = texture(shadowMap, TexCoords).r;
    FragColor = vec4(vec3(depthValue), 1.0); // orthographic

    // ### FragColor = vec4(1.0, 0.0, 1.0, 1.0);
}
