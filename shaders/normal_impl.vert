// NORMAL_IMPL //

void Normal_setup()
{
    mat3 normalMatrix = transpose(inverse(mat3(modelMatrix)));
    vec3 T = normalize(normalMatrix * in_tangent);
    vec3 B = normalize(normalMatrix * in_bitangent);
    vec3 N = normalize(normalMatrix * in_normal);    
    
    mat3 TBN = transpose(mat3(T, B, N));  
	var_toCameraVector = TBN * var_toCameraVector;
	
	
	for (int i = 0; i < lights.pointLightsCount; i++)
		var_toPointLightVectors[i] = TBN * var_toPointLightVectors[i];
	
	// acertar as luzes direcionais
}
