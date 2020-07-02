precision mediump float;
uniform samplerCube u_textureCube0;
varying vec3 v_posW;
void main()
{
   gl_FragColor = textureCube(u_textureCube0, vec3(v_posW.x, -v_posW.y, v_posW.z));
   //gl_FragColor = vec4(v_posW.x, -v_posW.y, v_posW.z, 1.0);
}