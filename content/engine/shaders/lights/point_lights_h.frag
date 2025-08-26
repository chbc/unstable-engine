// POINT_LIGHTS_H //

// Functions
void PointLights_compute(vec3 normal, vec3 toCameraDirection, inout vec3 kd, inout vec3 ks);
float PointLights_getAttenuation(int lightIndex, vec3 toPointLightVector);
