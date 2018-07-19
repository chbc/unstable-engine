// LIGHTS_H //

// Uniform variables
uniform vec3 ambientLightColor;
uniform float shininess;

// Functions
vec3 Lights_computeAmbientLight(vec3 materialColor);
void Lights_computeDiffuseAndSpecularLights(vec3 normal, inout vec3 kd, inout vec3 ks);
void Lights_computeEnergies(vec3 normal, vec3 toCameraDirection, vec3 toLightVector, inout float diffuseEnergy, inout float specularEnergy);
