precision mediump float;
uniform sampler2D u_texture2D0;
uniform sampler2D u_texture2D1;
varying vec2 v_textcoordL;
void main(void)
{
	vec4 color = texture2D(u_texture2D0, v_textcoordL);
	vec4 blur = texture2D(u_texture2D1, v_textcoordL);
	gl_FragColor = color + 1.2 * blur;
}