// MAIN_IMPL //

void main(void)
{
    vec3 ka = vec3(1.0);
    vec3 kd = vec3(0.0);
    vec3 ks = vec3(0.0);

    // [LIGHTS] ka = Lights_computeAmbientLight(materialColor.rgb);
    // [LIGHTS] vec3 normal = normalize(var_normal);
    // [NORMAL] normal = Normal_computeNormal();
    // [LIGHTS] Lights_computeDiffuseAndSpecularLights(normal, kd, ks);

    ka *= materialColor.rgb;
    kd *= materialColor.rgb;
    ks *= materialColor.rgb;

    // [AO] AmbientOclusion_computeAO(ka);

    // [SPECULAR] Specular_computeSpecular(ks);

    out_color = vec4(ka + kd + ks, 1.0);

    // [DIFFUSE] out_color = Diffuse_computeTextureColor(ka, kd, ks);
}
