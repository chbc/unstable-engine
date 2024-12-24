#version 330 core
uniform vec3 lightPosition;
uniform float farPlane;

in vec4 var_fragmentPosition;

void main()
{
    // get distance between fragment and light source
    float lightDistance = length(var_fragmentPosition.xyz - lightPosition);
    
    // map to [0;1] range by dividing by far_plane
    lightDistance = lightDistance / farPlane;
    
    // write this as modified depth
    gl_FragDepth = lightDistance;
}
