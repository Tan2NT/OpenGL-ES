precision mediump float;
uniform sampler2D u_texture2D0;
uniform float u_limit;
varying vec2 v_textcoordL;

void main(void)
{
	vec3 color = texture2D(u_texture2D0, v_textcoordL).rgb;
	float brightness = 0.3 * color.r + 0.59 * color.g + 0.11 * color.b;
	float val = step(u_limit, brightness);
	gl_FragColor = vec4(color * val, 1.0);
}
