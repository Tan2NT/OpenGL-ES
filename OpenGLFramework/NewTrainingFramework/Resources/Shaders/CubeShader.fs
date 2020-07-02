precision mediump float;
varying vec3 v_pos;
uniform samplerCube u_texture0;

void main()
{
	gl_FragColor = textureCube(u_texture0, v_pos);
}
