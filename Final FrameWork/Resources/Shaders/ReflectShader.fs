precision mediump float;
uniform samplerCube u_textureCube0;
uniform vec3 u_posCameraW;
varying vec3 v_posW;
varying vec3 v_normalW;
void main()
{
   vec3 toEye = u_posCameraW - v_posW;
   vec3 reflectDir = reflect(-toEye, normalize(v_normalW));
   gl_FragColor = textureCube(u_textureCube0, normalize(reflectDir));
}