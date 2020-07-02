precision mediump float;
uniform sampler2D u_texture2D0;
varying		vec2 v_textcoordL;
void main()
{
	gl_FragColor = texture2D(u_texture2D0, v_textcoordL);
}