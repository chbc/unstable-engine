// MAIN_IMPL //

void main(void)
{
    vec3 ka = vec3(1.0);
    vec3 kd = vec3(0.0);
    vec3 ks = vec3(0.0);

    ka *= materialColor.rgb;
    kd *= materialColor.rgb;
    ks *= materialColor.rgb;

    gl_FragColor = vec4(ka + kd + ks, 1.0);
	// [DIFFUSE] gl_FragColor = Diffuse_computeTextureColor(ka, kd, ks);
}
