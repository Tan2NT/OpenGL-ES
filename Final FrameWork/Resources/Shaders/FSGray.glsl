precision mediump float;
uniform sampler2D u_texture2D0;
varying		vec2 v_textcoordL;
void main()
{
	vec4 color = texture2D(u_texture2D0, v_textcoordL);
	float brightness = 0.3 * color.r + 0.59 * color.g + 0.11 * color.b;
	gl_FragColor = vec4(brightness, brightness, brightness, 1.0);
}