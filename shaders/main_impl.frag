// MAIN_IMPL //

void main(void)
{
	vec3 ka = Lights_computeAmbientLight(materialColor.rgb);
	vec3 kd = vec3(0.0);
	vec3 ks = vec3(0.0);
	
	vec3 normal = normalize(var_normal);
	vec3 toCameraDirection = normalize(var_toCameraVector);
	
	// [NORMAL] normal = Normal_computeNormal();
	
	Lights_computeDirectionalLights(normal, toCameraDirection, kd, ks);
	Lights_computePointLights(normal, toCameraDirection, kd, ks);

	kd = kd * materialColor.rgb;
	ks = ks * materialColor.rgb;
	
	out_color = vec4(ka + kd + ks, 1.0);
	
	// [DIFFUSE] out_color = Diffuse_computeTextureColor(ka, kd, ks);
}
